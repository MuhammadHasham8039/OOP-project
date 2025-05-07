#include "raylib.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>  
#include<vector>
using namespace std;
class Resources {
public:
    int food = 1000;
    int wood;
    int stone;
    int iron;

    Resources() : food(0), wood(0), stone(0), iron(0) {}
};
struct Economy {
    float gold;
    float debt;         // when the gold gets less than zero
    float taxRate;
    float inflation;
    float interestRate;
    float corruption;

    Economy() : gold(0.0f), debt(0.0f), taxRate(1.0f), inflation(0.0f), interestRate(0.05f), corruption(0.0f) {}
};
enum KingSkin {
    DEFAULT,
    SKIN1,
    SKIN2
};

KingSkin kingSkin = DEFAULT;

// this will devide the population into segments like peasents merchants and nobels
struct SocialClass {
    const char* name;
    int population;
    float unrest;

    SocialClass() : name(""), population(0), unrest(0.0f) {}
};

class Population :public Resources {
public:
    int currentPopulation;
    int employmentRate;

    Population() {}
    Population(int initialPopulation, int employmentRate, int wealth)
        : currentPopulation(initialPopulation), employmentRate(employmentRate) {
    }

    // replicating the effects of resources on population
    void UpdatePopulation() {
        if (food < 50) {
            currentPopulation -= 5;
        }
        else if (employmentRate > 80) {
            currentPopulation += 10;
        }
    }

    void DisplayPopulation(int x, int y) {
        string populationData = "Population: " + to_string(currentPopulation) +
            "\nFood Supply: " + to_string(food) +
            "\nEmployment Rate: " + to_string(employmentRate);

        DrawText(populationData.c_str(), x, y, 20, WHITE);
    }


};

class Military : public Resources {
public:
    int soldiers;
    int morale;
    float training; // percentage of training skills
    int pay;
    int swords;
    int arrows;
    int armours;
    int corruption;
    int costToTrain = 10;
    int trainCoins;
    string message;

    Military() : message("") {}
    Military(int soldiersCount, int morale, int pay, int corruption, int trainCoins, int training)
        :training(training), trainCoins(trainCoins), soldiers(soldiersCount), morale(morale), pay(pay), corruption(corruption) {
    }

    void displayinventory()
    {
        cout << soldiers << " Soldiers.\n";
        cout << swords << " Swords.\n";
        cout << arrows << " Arrows.\n";
        cout << armours << " Armours.\n";

    }

    void Recruit(int population, int x, int y) {
        // recruit 10 percent of the population on call
        int newSoldiers = population / 10;
        soldiers += newSoldiers;
        message = "Recruited " + to_string(newSoldiers) + " soldiers!";
        if (!message.empty()) {
            DrawText(message.c_str(), x, y, 20, YELLOW);
        }
    }

    void TrainSoldiers(int number, int x, int y) {
        if (trainCoins > (number * costToTrain)) {
            morale += 10;
            training += 10;
            pay += 10;
            trainCoins -= (number * costToTrain);
            message = "Training..Morale increased";
        }
        else {
            message = "Not enough resources ";
        }
        if (!message.empty()) {
            DrawText(message.c_str(), x, y, 20, RED);
        }
    }

    void UpdateMilitary() {
        if (food < 50) {
            morale -= 10;
        }

        if (pay < 50) {
            morale -= 15;
        }

        if (morale < 50) {
            soldiers -= 5;
        }

        if (corruption > 50) {
            morale -= 20;
            std::cout << "Corruption is high, morale is decreasing" << endl;
        }
    }

    void DisplayMilitary(int x, int y) {
        string militaryData = "Soldiers: " + to_string(soldiers) +
            "\n morale: " + to_string(morale) + " %" +
            "\n pay: " + to_string(pay) +
            "\n corruption: " + to_string(corruption) + " %";

        DrawText(militaryData.c_str(), x, y, 20, WHITE);
    }


    void IncreaseCorruption() {
        corruption += 5;  // Corruption increases over time
    }
};

enum LeadershipStyle {
    AUTHORITARIAN,
    DEMOCRATIC,
    ECONOMIC
};
struct EventLog {
    static const int MAX_EVENTS = 5;
    char messages[MAX_EVENTS][128];
    int count;

    EventLog() : count(0) {
        for (int i = 0; i < MAX_EVENTS; ++i) {
            messages[i][0] = '\0';
        }
    }

    void add(const char* msg) {
        if (count < MAX_EVENTS) {
            strcpy_s(messages[count], sizeof(messages[count]), msg);
            count++;
        }
        else {
            for (int i = 1; i < MAX_EVENTS; ++i) {
                strcpy_s(messages[i - 1], sizeof(messages[i - 1]), messages[i]);
            }
            strcpy_s(messages[MAX_EVENTS - 1], sizeof(messages[MAX_EVENTS - 1]), msg);
        }
    }
};

class Leadership {
public:
    string title;
    int approvalRating;
    bool isAlive;
    int age;
    string message;
    LeadershipStyle style;
    string name;
    int term;
    float popularityfactor;
    EventLog eventleadership;
    int x = 1050;
    int y = 600;

    Leadership() : isAlive(true), message(""), style(AUTHORITARIAN), term(0), popularityfactor(1.0f), name("King") {}

    void addEvent(const char* msg) {
        eventleadership.add(msg);
    }

    // add to castle 
    void DisplayLeadership() {

        string styleText;
        switch (style) {
        case AUTHORITARIAN: styleText = "Authoritarian"; break;
        case DEMOCRATIC: styleText = "DEMOCRATIC"; break;
        case ECONOMIC: styleText = "Economic"; break;
        default: styleText = "Unknown"; break;
        }

        string leadershipData = title + " " + name + " (" + styleText + ")" +
            "\nLeadership Approval: " + to_string(approvalRating) + "%" +
            "\nYears in Power: " + to_string(term);
        DrawText(leadershipData.c_str(), x, y, 20, RED);
    }
    // castle menue
    void DisplayLeadershipPolicies() {
        string policyText;
        switch (style) {
        case AUTHORITARIAN:
            policyText = "Authoritarian Policies \n military strength \n noble support \n higher taxes \n peasents unrest ";

            break;
        case DEMOCRATIC:
            policyText = "DEMOCRATIC Policies \n Reduced Civil Unrest \n Popular Support \n Lower Tax Revenue";
            break;
        case ECONOMIC:
            policyText = "Economic Policies \n Increased Gold \n Lower Corruption\n  Merchant Support \n Lower Inflation";
            break;
        default:
            policyText = "Unknown Policy";
            break;
        }

        DrawText(policyText.c_str(), x, y, 18, LIGHTGRAY);
    }

    bool checkElection() {
        if (approvalRating < 30) {
            message = "The leadership is weak. An election will take place!";
            isAlive = false;
            return true;
        }
        else {
            message = "The leadership has the majority";
            return false;
        }
        if (!message.empty()) {
            addEvent(message.c_str());
        }
    }


    void DeathInBattle() {
        if (isAlive && approvalRating < 10) {
            message = "The leader has died in battle due to low morale";
            isAlive = false;
            addEvent(message.c_str());
        }
    }

    void AgeLeader() {
        term++;
        // after 60 the popularity of king will start to fall
        if (age > 60) {
            popularityfactor *= 0.90f;
        }
    }

    // all the policies which were discussed earlier will be implemented as the leadership has taken over the kingdom
    void ImplementPolicy(Economy& economy, SocialClass& peasants, SocialClass& merchants,
        SocialClass& nobles, Military& army, Resources& resources) {
        switch (style) {
        case AUTHORITARIAN:
            economy.taxRate *= 1.5f;
            peasants.unrest += 2.0f;
            merchants.unrest += 2.0f;
            nobles.unrest -= 1.0f;
            army.morale += 3.0f;
            break;

        case DEMOCRATIC:
            economy.taxRate *= 0.5f;
            peasants.unrest -= 3.0f;
            merchants.unrest -= 2.0f;
            nobles.unrest -= 1.0f;
            resources.food *= 2.0f;
            break;

        case ECONOMIC:
            economy.corruption *= 0.5f;
            economy.inflation *= 0.6f;
            merchants.unrest -= 3.0f;
            economy.gold *= 1.5f;
            break;
        }
        // managing the out of range 
        if (economy.taxRate > 2.0f) economy.taxRate = 2.0f;
        if (economy.taxRate < 0.5f) economy.taxRate = 0.5f;
    }


    // now after the king has died or has lost popularity the regime will change and there are few ways in which it can be done

    void TransitionPower() {

        style = static_cast<LeadershipStyle>(rand() % 3);

        const char* firstNames[] = { "mulla jutt", "chahcu", "chachi" };
        name = string(firstNames[rand() % 3]);
        // after the new king is selcted the stats will be reset for the new regime
        isAlive = true;
        age = 30 + rand() % 30;
        approvalRating = 50 + rand() % 30;
        popularityfactor = 1.0f;
        term = 0;


        switch (style) {
        case AUTHORITARIAN: title = "badshah"; break;
        case DEMOCRATIC: title = "prime minister"; break;
        case ECONOMIC: title = "master"; break;
        default: title = "King"; break;
        }

        message = title + " " + name + " has taken power!";
        addEvent(message.c_str());

    }
    // this will be used for death in war as wwll
    void warORmoraleTransition() {
        isAlive = true;
        age = 30 + rand() % 30;
        approvalRating = 60 + rand() % 20;
        popularityfactor = 1.1f;
        term = 0;

        style = (rand() % 2) ? DEMOCRATIC : ECONOMIC;


        const char* firstNames[] = { "mola jutt", "chahcu", "nigga" };
        name = string(firstNames[rand() % 3]);

        switch (style) {
        case AUTHORITARIAN: title = "badshah"; break;
        case DEMOCRATIC: title = "prime minister"; break;
        case ECONOMIC: title = "master"; break;
        default: title = "King"; break;
        }

        message = title + " " + name + " has been elected!";
        addEvent(message.c_str());

    }
};

struct Building {
    string name;
    Rectangle rect;
    Color color;

};

class Kingdom {
public:
    int day;
    SocialClass peasants;
    SocialClass merchants;
    SocialClass nobles;
    Leadership leader;
    Military army;
    Economy economy;
    Resources resources;
    EventLog events;
    Population total;

    void handleleadership() {
        string message;
        leader.AgeLeader();

        leader.ImplementPolicy(economy, peasants, merchants, nobles, army, resources);

        // check for natural death 
        if (leader.age > 60) {
            int death = rand() % 2;

            if (death == 1) {
                leader.isAlive = false;
                char deathMsg[128];
                string message = string(leader.title) + " " + leader.name + " has died of old age at " + to_string(leader.age) + ".";
                strcpy_s(deathMsg, sizeof(deathMsg), message.c_str());
                addEvent(deathMsg);
            }
        }
        // death in the battles field is dependent on the morale of the army
        if (army.morale < 20.0f) {
            leader.DeathInBattle();
            if (!leader.isAlive) {
                addEvent("leader has died in battle");
            }
        }


        // now deciding the method of transition of regime on the basis of factors which affected the part regime

        if (!leader.isAlive) {

            if (strstr(events.messages[events.count - 1], "fallen in battle") != NULL) {
                leader.warORmoraleTransition();
                message = "After the battle, " + leader.title + " " + leader.name + " has been appointed!";
                addEvent(message.c_str());

            }
            else {
                leader.TransitionPower();
                message = "A new leader has been crowned: " + leader.title + " " + leader.name;
                addEvent(message.c_str());
            }
        }

        // Check for election if approval is too low
        if (leader.approvalRating < 20 && rand() % 100 < 30) {
            if (leader.checkElection()) {
                addEvent("The leader has been voted out of office due to low approval!");
                leader.warORmoraleTransition();
                string message = leader.title + " " + leader.name + " has been elected!";
                addEvent(message.c_str());
            }
        }
    }

    int warChance = 30;

    Kingdom() {
        day = 0;
        peasants.name = "Peasants";
        peasants.population = 100;
        peasants.unrest = 0.0;
        merchants.name = "Merchants";
        merchants.population = 30;
        merchants.unrest = 0.0;
        nobles.name = "Nobles";
        nobles.population = 10;
        nobles.unrest = 0.0;
        leader.title = "King";
        leader.age = 40;
        army.soldiers = 20;
        army.training = 50.0;
        army.morale = 80.0;
        army.corruption = 0.0;
        economy.gold = 500.0;
        economy.debt = 0.0;
        economy.taxRate = 1.0;
        economy.inflation = 0.0;
        economy.interestRate = 0.05;
        economy.corruption = 0.1;
        resources.food = 200;
        resources.wood = 150;
        resources.stone = 50;
        resources.iron = 130;

        total.currentPopulation = peasants.population + merchants.population + nobles.population + army.soldiers;
    }

    void addEvent(const char* msg) {
        events.add(msg);
    }

    void updateday() {
        day += 1;

        int p = peasants.population;
        int foodProduced = (int)(p * 1.0f);
        int woodProduced = (int)(p * 1.0f);
        int stoneProduced = (int)(p * 1.0f);
        int ironProduced = (int)(p * 1.0f);

        resources.food += foodProduced;
        resources.wood += woodProduced;
        resources.stone += stoneProduced;
        resources.iron += ironProduced;

        int totalPopulation = peasants.population + merchants.population + nobles.population;
        int foodNeeded = totalPopulation;
        foodNeeded += army.soldiers;
        if (resources.food < foodNeeded) {
            int deficit = foodNeeded - resources.food;
            int deaths = deficit;
            int pdeaths = deaths;
            if (pdeaths > peasants.population) pdeaths = peasants.population;
            peasants.population -= pdeaths;
            deaths -= pdeaths;
            if (deaths > 0) {
                int m_deaths = deaths;
                if (m_deaths > merchants.population) m_deaths = merchants.population;
                merchants.population -= m_deaths;
                deaths -= m_deaths;
            }
            if (deaths > 0) {
                int n_deaths = deaths;
                if (n_deaths > nobles.population) n_deaths = nobles.population;
                nobles.population -= n_deaths;
                deaths -= n_deaths;
            }
            resources.food = 0;
            peasants.unrest += 20.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            merchants.unrest += 10.0f;
            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            nobles.unrest += 5.0f;
            if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
            addEvent("famine: Severe food shortage");
        }
        else {
            resources.food -= foodNeeded;
        }

        int woodNeeded = (int)(totalPopulation * 0.1);
        if (resources.wood < woodNeeded) {
            resources.wood = 0;
            peasants.unrest += 5.0;
            merchants.unrest += 3.0;
            nobles.unrest += 1.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0;
            if (merchants.unrest > 100.0) merchants.unrest = 100.0f;
            if (nobles.unrest > 100.0f) nobles.unrest = 100.0;
            addEvent("Hardship: Wood supplies khatam");
        }
        else {
            resources.wood -= woodNeeded;
        }

        if (army.soldiers > 0) {
            int ironNeeded = (int)(army.soldiers * 0.1);
            if (resources.iron < ironNeeded) {
                army.morale -= 5.0;
                if (army.morale < 0.0) army.morale = 0.0;
                resources.iron = 0;
                addEvent("Shortage: Iron is end");
            }
            else {
                resources.iron -= ironNeeded;
            }
        }


        float baseTax = peasants.population * 1.0f + merchants.population * 3.0f + nobles.population * 0.0f;
        float grossTaxIncome = baseTax * economy.taxRate;
        float netTaxIncome = grossTaxIncome * (1.0f - economy.corruption);
        economy.gold += netTaxIncome;
        float economySize = (float)totalPopulation + resources.food * 0.5;
        if (economy.gold > economySize * 5.0f) {
            economy.inflation += 0.02f;
            if (economy.inflation > 1.0f) economy.inflation = 1.0f;
        }
        float salaryCost = army.soldiers * 1.0f;
        if (economy.gold < salaryCost) {
            float shortfall = salaryCost - economy.gold;
            economy.gold = 0;
            float moraleDrop = (shortfall / salaryCost) * 20.0f;
            army.morale -= moraleDrop;
            if (army.morale < 0.0f) army.morale = 0;
            army.corruption += 0.05;
            if (army.corruption > 1.0) army.corruption = 1.0;
            addEvent("Financial: Unable to pay all soldiers");
        }
        else {
            economy.gold -= salaryCost;
            army.morale += 1.0f;
            if (army.morale > 100.0f) army.morale = 100.0f;
        }

        army.training += 2.0f;
        if (army.training > 100.0f) army.training = 100.0f;
        if (army.morale > 50.0f) {
            army.morale -= 0.5f;
            if (army.morale < 50.0f) army.morale = 50.0f;
        }
        else if (army.morale < 50.0f) {
            army.morale += 0.5f;
            if (army.morale > 50.0f) army.morale = 50.0f;
        }

        float birthRate = 0.02f;
        float deathRate = 0.01f;
        int peasantsBirths = (int)(peasants.population * birthRate);
        int merchantsBirths = (int)(merchants.population * birthRate);
        int noblesBirths = (int)(nobles.population * birthRate);
        int peasantsDeaths = (int)(peasants.population * deathRate);
        int merchantsDeaths = (int)(merchants.population * deathRate);
        int noblesDeaths = (int)(nobles.population * deathRate);
        peasants.population += peasantsBirths - peasantsDeaths;
        merchants.population += merchantsBirths - merchantsDeaths;
        nobles.population += noblesBirths - noblesDeaths;
        if (peasants.population < 0) peasants.population = 0;
        if (merchants.population < 0) merchants.population = 0;
        if (nobles.population < 0) nobles.population = 0;
        totalPopulation = peasants.population + merchants.population + nobles.population;

        leader.age += 1;

        if (leader.age > 60) {
            int deathRoll = rand() % 100;
            if (deathRoll < (leader.age - 60)) {
                char deathMsg[128];

                string message = string(leader.title) + " has died of old age at " + to_string(leader.age) + ".";

                strcpy_s(deathMsg, message.c_str());

                addEvent(deathMsg);
            }
        }



        int random100 = rand() % 100;
        int random100b = rand() % 100;
        bool eventOccurred = false;

        if (army.soldiers > peasants.population / 2) {
            warChance += 20;
        }
        if (!eventOccurred && random100 < warChance) {
            eventOccurred = true;
            bool victory = (army.training > 70 && army.morale > 50 && army.soldiers > 10) && (rand() % 100 < 50);
            int initialSoldiers = army.soldiers;
            int soldierLoss = victory ? (army.soldiers * 10 / 100) : (army.soldiers * 30 / 100);
            if (soldierLoss < 1 && army.soldiers > 0) soldierLoss = 1;
            army.soldiers -= soldierLoss;
            if (army.soldiers < 0) army.soldiers = 0;
            int peasantLoss = victory ? (peasants.population * 2 / 100) : (peasants.population * 5 / 100);
            peasants.population -= peasantLoss;
            if (peasants.population < 0) peasants.population = 0;
            int foodUse = 20;
            if (resources.food < foodUse) foodUse = resources.food;
            resources.food -= foodUse;
            int woodUse = 15;
            if (resources.wood < woodUse) woodUse = resources.wood;
            resources.wood -= woodUse;
            int stoneUse = 10;
            if (resources.stone < stoneUse) stoneUse = resources.stone;
            resources.stone -= stoneUse;
            int ironUse = 10;
            if (resources.iron < ironUse) ironUse = resources.iron;
            resources.iron -= ironUse;
            float warCost = 50.0f;
            if (economy.gold < warCost) {
                economy.debt += (warCost - economy.gold);
                economy.gold = 0.0f;
            }
            else {
                economy.gold -= warCost;
            }
            if (victory) {
                army.morale += 5.0f;
                if (army.morale > 100.0f) army.morale = 100.0f;
            }
            else {
                army.morale -= 10.0f;
                if (army.morale < 0.0f) army.morale = 0.0f;
            }
            economy.inflation += 0.01f;
            if (economy.inflation > 1.0f) economy.inflation = 1.0f;
            peasants.unrest += 5.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            merchants.unrest += 3.0f;
            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            char warMsg[128];
            string message;

            if (victory) {
                message = "War: Victory We lost " + to_string(soldierLoss) + " of " + to_string(initialSoldiers) + " soldiers.";
            }
            else {
                message = "War: Defeat... We lost " + to_string(soldierLoss) + " of " + to_string(initialSoldiers) + " soldiers.";
            }

            strcpy_s(warMsg, sizeof(warMsg), message.c_str());

            addEvent(warMsg);

        }

        handleleadership();
    }





    // AI CONTROL DECISON MAKING 
    // the system is designed to make decisons on the basis of stats 

    void ManageResources() {
        if (resources.food < (peasants.population + merchants.population + nobles.population)) {
            // if the food production is low we will allocate more population to the production
            int peasantsForFood = peasants.population * 0.5f;
            resources.food += peasantsForFood * 1;

            addEvent("Allocated more peasants to food production.");

            // if still we will have less food we will trade from the market 
            // in future can trade with other kingdoms as well
            if (resources.food < (peasants.population + merchants.population + nobles.population)) {
                if (economy.gold >= 50) {
                    resources.food += 50;
                    economy.gold -= 50;
                    addEvent("traded gold for food.");
                }
                else {
                    addEvent("Gold is not enought");
                }
            }
        }

        if (resources.wood < (peasants.population + merchants.population + nobles.population) * 0.1f) {
            int peasantsForWood = peasants.population * 0.2f;
            resources.wood += peasantsForWood * 1;
            addEvent("Allocated more people for wood collection.");

            if (resources.wood < 20 && economy.gold >= 30) {
                resources.wood += 30;
                economy.gold -= 30;
                addEvent("Traded gold for wood.");
            }
        }

        if (resources.iron < army.soldiers * 1) {
            int peasantsForIron = peasants.population * 0.1f;
            resources.iron += peasantsForIron * 1;
            addEvent("Allocated more peasants to iron mining.");
        }
    }

    void ManageMilitary() {
        if (army.soldiers < 50) {
            int recruits = peasants.population / 10;
            army.soldiers += recruits;
            addEvent("Recruited new soldiers.");
        }

        if (army.morale < 50 && economy.gold >= army.soldiers * 1.0f) {
            // training the soldiers require gold 
            army.morale += 10;
            economy.gold -= army.soldiers * 1;
            addEvent("Training soldiers to boost morale.");
        }

        if (army.soldiers > 50 && economy.gold > 200) {
            // warchance more than 50 result in war
            if (warChance > 50) {
                // the victory will be based on the morale of the army
                bool victory = army.morale > 50;

                army.soldiers -= victory ? army.soldiers * 0.1 : army.soldiers * 0.3;
                economy.gold -= 50;
                if (victory) {
                    army.morale += 5;
                    addEvent("Victory in war confidence is increased");
                }
                else {
                    army.morale -= 10;
                    addEvent("Defeat in war.  morale decreased.");
                }
            }
        }
    }

    void ManageEconomy() {
        if (economy.gold < 100.0f) {
            economy.taxRate = 0.5f;
            economy.debt += 50.0f;
            addEvent("Economic Crisis: Taxes reduced, debt increased");
        }
        else {
            economy.taxRate = 1.0f;
        }

        if (economy.gold > 1000.0f) {
            economy.inflation += 0.02f;
            if (economy.inflation > 1.0f) economy.inflation = 1.0f;
        }

        if (economy.debt > 1000.0f) {
            economy.debt *= 0.9f;
            economy.inflation += 0.05f;
            addEvent("Debt Reduction: Paid down debt at the cost of inflation.");
        }

        if (economy.gold < 50.0f) {
            // trading food back for gold
            addEvent("Warning: low on gold");
            if (resources.food > 50) {
                resources.food -= 10;
                economy.gold += 10;
                addEvent("Traded food for gold.");
            }
        }
    }

    void AIControl() {
        updateday();
        ManageResources();
        ManageMilitary();
        ManageEconomy();
    }

};


class RenderSystem {

private:
    Building buildings[10];
    int buildingCount;
    Rectangle chiefPosition;
    Rectangle newKingdomChiefPosition; // Added for new kingdom chief
    float gridSize;
    int screenWidth;
    int screenHeight;
    float nextEventTime = 10.0f; // Track time for random events
    int x = screenWidth - 260; // side window position
    int y;
    string messagemenue;
    int  currentLevel = 1;
    Kingdom kingdom;
    Population population;
    Military military;
    Leadership leadership;
    // Military army;
    vector<Kingdom> additionalKingdoms;
    int currentKingdomIndex = -1; // -1 means main kingdom, 0+ means additional kingdoms

    // Add texture for the chief in new kingdom
    Texture2D newKingdomChiefTexture;
    bool newKingdomChiefTextureLoaded = false;
public:
    // Add a method to load the new chief texture
    void LoadNewKingdomChiefTexture() {
        if (!newKingdomChiefTextureLoaded) {
            // Check if file exists
            if (FileExists("kingc2.png")) {
                Image chiefImage = LoadImage("kingc2.png");
                if (chiefImage.data != NULL) {
                    newKingdomChiefTexture = LoadTextureFromImage(chiefImage);
                    UnloadImage(chiefImage);
                    newKingdomChiefTextureLoaded = true;
                }
                else {
                    // Handle error - image failed to load
                    printf("Failed to load chief image\n");
                }
            }
            else {
                // Handle error - file doesn't exist
                printf("Chief image file not found\n");
            }
        }
    }

    // Add a method to unload the texture
    void UnloadNewKingdomChiefTexture() {
        if (newKingdomChiefTextureLoaded) {
            UnloadTexture(newKingdomChiefTexture);
            newKingdomChiefTextureLoaded = false;
        }
    }

    // Update the new kingdom chief movement
    void UpdateNewKingdomChiefMovement() {
        if (IsKeyPressed(KEY_RIGHT) && newKingdomChiefPosition.x + gridSize < screenWidth)
            newKingdomChiefPosition.x += gridSize;
        if (IsKeyPressed(KEY_LEFT) && newKingdomChiefPosition.x > 0)
            newKingdomChiefPosition.x -= gridSize;
        if (IsKeyPressed(KEY_DOWN) && newKingdomChiefPosition.y + gridSize < screenHeight)
            newKingdomChiefPosition.y += gridSize;
        if (IsKeyPressed(KEY_UP) && newKingdomChiefPosition.y > 0)
            newKingdomChiefPosition.y -= gridSize;
    }

    // Update the newwindow method to include chief movement
    // Add new buildings for the new kingdom
    Building newKingdomBuildings[5];

    void InitNewKingdomBuildings() {
        // Initialize buildings for the new kingdom
        newKingdomBuildings[0] = { "New Castle", {150, 150, (float)gridSize, (float)gridSize}, DARKGRAY };
        newKingdomBuildings[1] = { "New Barracks", {350, 250, (float)gridSize, (float)gridSize}, RED };
        newKingdomBuildings[2] = { "New Market", {550, 350, (float)gridSize, (float)gridSize}, ORANGE };
        newKingdomBuildings[3] = { "New Blacksmith", {200, 350, (float)gridSize, (float)gridSize}, BROWN };
        newKingdomBuildings[4] = { "New Church", {450, 150, (float)gridSize, (float)gridSize}, PURPLE };
    }

    void DrawNewKingdomBuildings() {
        for (int i = 0; i < 5; i++) {
            bool isNear = CheckCollisionRecs(newKingdomChiefPosition, newKingdomBuildings[i].rect);
            Color drawColor = isNear ? GOLD : newKingdomBuildings[i].color;

            DrawRectangleRec(newKingdomBuildings[i].rect, drawColor);
            DrawText(newKingdomBuildings[i].name.c_str(),
                newKingdomBuildings[i].rect.x + 5,
                newKingdomBuildings[i].rect.y + gridSize + 5,
                12, WHITE);

            if (isNear) {
                DrawText(("Entered: " + newKingdomBuildings[i].name).c_str(),
                    10, 480, 18, MAROON);
            }
        }
    }

    void HandleNewKingdomBuildingInteractions(Kingdom& currentKingdom) {
        // Check for collision with buildings and handle interactions
        for (int i = 0; i < 5; i++) {
            if (CheckCollisionRecs(newKingdomChiefPosition, newKingdomBuildings[i].rect)) {
                // Different menus based on building type
                if (newKingdomBuildings[i].name == "New Castle") {
                    DrawText("New Castle Menu", 20, 530, 20, RED);
                    DrawText("1. Check Kingdom Status", 20, 555, 20, BLACK);
                    DrawText("2. Change Leadership Style", 20, 580, 20, BLACK);

                    if (IsKeyPressed(KEY_ONE)) {
                        char statusMsg[128];
                        sprintf_s(statusMsg, sizeof(statusMsg), "Kingdom Status: %s rule, %d approval",
                            currentKingdom.leader.title.c_str(),
                            currentKingdom.leader.approvalRating);
                        currentKingdom.addEvent(statusMsg);
                    }
                    else if (IsKeyPressed(KEY_TWO)) {
                        currentKingdom.leader.style = static_cast<LeadershipStyle>(
                            (static_cast<int>(currentKingdom.leader.style) + 1) % 3);
                        char styleMsg[128];
                        sprintf_s(styleMsg, sizeof(styleMsg), "Changed leadership style to %d",
                            static_cast<int>(currentKingdom.leader.style));
                        currentKingdom.addEvent(styleMsg);
                    }
                }
                else if (newKingdomBuildings[i].name == "New Barracks") {
                    DrawText("New Barracks Menu", 20, 530, 20, RED);
                    DrawText("1. Train Troops (+5 morale)", 20, 555, 20, BLACK);
                    DrawText("2. Recruit Soldiers (10% of peasants)", 20, 580, 20, BLACK);

                    if (IsKeyPressed(KEY_ONE)) {
                        if (currentKingdom.economy.gold >= 20) {
                            currentKingdom.army.morale += 5;
                            currentKingdom.economy.gold -= 20;
                            currentKingdom.addEvent("Troops trained. Morale increased.");
                        }
                        else {
                            currentKingdom.addEvent("Not enough gold to train troops.");
                        }
                    }
                    else if (IsKeyPressed(KEY_TWO)) {
                        int recruits = currentKingdom.peasants.population / 10;
                        if (recruits > 0) {
                            currentKingdom.army.soldiers += recruits;
                            currentKingdom.peasants.population -= recruits;
                            char recruitMsg[128];
                            sprintf_s(recruitMsg, sizeof(recruitMsg), "Recruited %d new soldiers", recruits);
                            currentKingdom.addEvent(recruitMsg);
                        }
                        else {
                            currentKingdom.addEvent("Not enough peasants to recruit.");
                        }
                    }
                }
                // Additional building interactions can be added here
            }
        }
    }

    void SelectKingSkin() {
        bool skinMenuActive = true;

        while (skinMenuActive && !WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);

            Image character = LoadImage("kinga.PNG");
            Texture2D tex = LoadTextureFromImage(character);
            UnloadImage(character);
            DrawTexture(tex, 430, 200, WHITE);

            Image chara = LoadImage("kingccrop.PNG");
            Texture2D texa = LoadTextureFromImage(chara);
            UnloadImage(chara);
            DrawTexture(texa, 30, 200, WHITE);

            Image charaa = LoadImage("chachu400.PNG");
            Texture2D texaa = LoadTextureFromImage(charaa);
            UnloadImage(charaa);
            DrawTexture(texaa, 800, 120, WHITE);

            Rectangle titleButtonRect = { 430, 10, 380, 60 };
            float borderRadius = 20.0f;
            DrawRectangleRounded(titleButtonRect, borderRadius, 0, GOLD);
            DrawText("Select King Skin", 455, 25, 40, BLACK);

            Rectangle optionABackground = { 80, 640, 200, 40 };
            DrawRectangleRounded(optionABackground, borderRadius, 0, DARKGRAY);
            DrawText("A. SON", 90, 650, 20, WHITE);

            Rectangle optionBBackground = { 520, 640, 200, 40 };
            DrawRectangleRounded(optionBBackground, borderRadius, 0, DARKGRAY);
            DrawText("B. ELDER SON", 530, 650, 20, WHITE);

            Rectangle optionCBackground = { 980, 640, 200, 40 };
            DrawRectangleRounded(optionCBackground, borderRadius, 0, DARKGRAY);
            DrawText("C. CHACHU", 1000, 650, 20, WHITE);

            if (IsKeyPressed(KEY_A)) {
                kingSkin = DEFAULT;
                skinMenuActive = false;
            }
            else if (IsKeyPressed(KEY_B)) {
                kingSkin = SKIN1;
                skinMenuActive = false;
            }
            else if (IsKeyPressed(KEY_C)) {
                kingSkin = SKIN2;
                skinMenuActive = false;
            }

            if (IsKeyPressed(KEY_ESCAPE)) {
                skinMenuActive = false;
            }

            EndDrawing();
        }
    }


    void MainMenu() {
        int menuOption = 0;
        bool menuActive = true;

        while (menuActive && !WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);

            Image back = LoadImage("chachu1.JPG");
            Texture2D tex = LoadTextureFromImage(back);
            UnloadImage(back);
            DrawTexture(tex, 0, 0, WHITE);

            Rectangle startButtonRect = { 510, 590, 200, 50 };
            float borderRadius = 20.0f;
            DrawRectangleRounded(startButtonRect, borderRadius, 0, YELLOW);

            DrawText("A. Start Game", 520, 600, 25, BLACK);

            Rectangle quitButtonRect = { 510, 670, 200, 30 };
            DrawRectangleRounded(quitButtonRect, borderRadius, 0, YELLOW);

            DrawText("Press ESC to Quit", 520, 680, 20, BLACK);

            if (IsKeyPressed(KEY_A)) {
                menuOption = 1;
                menuActive = false;
            }

            if (IsKeyPressed(KEY_ESCAPE)) {
                CloseWindow();
            }

            EndDrawing();
        }
    }

    // update cheif movement
    void UpdateChiefMovement() {
        if (IsKeyPressed(KEY_RIGHT) && chiefPosition.x + gridSize < screenWidth) chiefPosition.x += gridSize;
        if (IsKeyPressed(KEY_LEFT) && chiefPosition.x > 0) chiefPosition.x -= gridSize;
        if (IsKeyPressed(KEY_DOWN) && chiefPosition.y + gridSize < screenHeight) chiefPosition.y += gridSize;
        if (IsKeyPressed(KEY_UP) && chiefPosition.y > 0) chiefPosition.y -= gridSize;
    }
    // building 0 menue display
    // not in use 
    void menueB0(int option) {
        switch (option) {
        case 1:
            military.DisplayMilitary(1050, 550);
            break;
        case 2:
            population.DisplayPopulation(1050, 550);
            break;
        case 3:
            leadership.DisplayLeadership();
            break;
        default:
            break;
        }
    }
    void DrawGrid() {
        for (int x = 0; x < screenWidth; x += gridSize)
            DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
        for (int y = 0; y < screenHeight; y += gridSize)
            DrawLine(0, y, screenWidth, y, LIGHTGRAY);
    }
    // anything like title on the corner 
    void Drawdiscription() const
    {
        string label = "LOONAYWALA";

        int fontSize = 20;
        int textW = MeasureText(label.c_str(), fontSize);
        int textH = fontSize;

        int padding = 8;
        int boxX = 10;
        int boxY = 10;
        int boxW = textW + padding * 2;
        int boxH = textH + padding * 2;

        DrawRectangleRounded({ (float)boxX, (float)boxY,
                               (float)boxW, (float)boxH }, 0.25f, 8, DARKBROWN);


        int textX = boxX + padding;
        int textY = boxY + padding;
        DrawText(label.c_str(), textX, textY, fontSize, BEIGE);
    }

    void DrawBuildings() {
        int spacing = gridSize * 3;

        for (int i = 0; i < buildingCount; i++) {
            DrawRectangleRec({ buildings[i].rect.x + 5, buildings[i].rect.y + 5, gridSize, gridSize }, Fade(BLACK, 0.2f));

            bool isNear = CheckCollisionRecs(chiefPosition, buildings[i].rect);
            Color drawColor = isNear ? GOLD : buildings[i].color;

            if (buildings[i].name == "Castle") {
                DrawRectangleRec(buildings[i].rect, DARKGRAY);
                DrawRectangle(buildings[i].rect.x - 10, buildings[i].rect.y - 40, gridSize / 4, gridSize / 3, DARKGRAY);
                DrawRectangle(buildings[i].rect.x + gridSize - 10, buildings[i].rect.y - 40, gridSize / 4, gridSize / 3, DARKGRAY);
                DrawRectangle(buildings[i].rect.x + gridSize / 4, buildings[i].rect.y + gridSize - 20, gridSize / 2, 20, BROWN);
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
            }

            else if (buildings[i].name == "Barracks") {
                DrawRectangleRec(buildings[i].rect, RED);
                DrawRectangle(buildings[i].rect.x + 5, buildings[i].rect.y - 15, gridSize - 20, 15, RED);
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y - 30, 10, 15, DARKBROWN);
                DrawRectangle(buildings[i].rect.x + 5, buildings[i].rect.y + 10, 30, 15, LIGHTGRAY);
                DrawRectangle(buildings[i].rect.x + gridSize - 40, buildings[i].rect.y + 10, 30, 15, LIGHTGRAY);
                DrawRectangle(buildings[i].rect.x + (gridSize / 2) - 20, buildings[i].rect.y + gridSize - 20, 40, 20, BROWN);
            }

            else if (buildings[i].name == "Market") {
                DrawRectangleRec(buildings[i].rect, ORANGE);
                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 20, gridSize - 20, 20, ORANGE);
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize - 20, gridSize - 30, 20, YELLOW);
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
            }

            else if (buildings[i].name == "Town Hall") {
                DrawRectangleRec(buildings[i].rect, BLUE);
                DrawRectangle(buildings[i].rect.x + gridSize / 3, buildings[i].rect.y - 30, gridSize / 3, 30, DARKBLUE);
                DrawTriangle({ buildings[i].rect.x + gridSize / 3, buildings[i].rect.y - 30 },
                    { buildings[i].rect.x + gridSize / 3 + gridSize / 6, buildings[i].rect.y - 60 },
                    { buildings[i].rect.x + gridSize / 3 + gridSize / 3, buildings[i].rect.y - 30 }, DARKBLUE);
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
            }

            else if (buildings[i].name == "Blacksmith") {
                DrawRectangleRec(buildings[i].rect, BROWN);
                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 15, gridSize - 20, 15, DARKBROWN);
                DrawRectangle(buildings[i].rect.x + gridSize / 3, buildings[i].rect.y + gridSize - 30, gridSize / 3, 15, DARKGRAY);
                DrawRectangle(buildings[i].rect.x + 20, buildings[i].rect.y - 30, 10, 15, DARKBROWN);
                DrawRectangle(buildings[i].rect.x + (gridSize / 2) - 20, buildings[i].rect.y + gridSize - 20, 40, 20, BROWN);
            }

            else if (buildings[i].name == "Church") {
                DrawRectangleRec(buildings[i].rect, PURPLE);
                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 15, gridSize - 20, 15, DARKPURPLE);
                DrawRectangle(buildings[i].rect.x + gridSize / 2 - 5, buildings[i].rect.y - 40, 10, 20, DARKPURPLE);
                DrawTriangle({ buildings[i].rect.x + gridSize / 2 - 5, buildings[i].rect.y - 40 },
                    { buildings[i].rect.x + gridSize / 2 + 5, buildings[i].rect.y - 60 },
                    { buildings[i].rect.x + gridSize / 2 + 15, buildings[i].rect.y - 40 }, DARKPURPLE);
                DrawLine(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y - 60, buildings[i].rect.x + gridSize / 2, buildings[i].rect.y - 75, WHITE);
                DrawLine(buildings[i].rect.x + gridSize / 2 - 10, buildings[i].rect.y - 67, buildings[i].rect.x + gridSize / 2 + 10, buildings[i].rect.y - 67, WHITE);
            }

            DrawText(buildings[i].name.c_str(), buildings[i].rect.x + 5, buildings[i].rect.y + 35, 10, WHITE);

            if (isNear) {
                DrawText(("Entered: " + buildings[i].name).c_str(), 10, 560, 18, MAROON);
            }
        }

    }
    // two characters of cheif
    void DrawChief2()
    {
        float headR = gridSize * 0.18f;
        float Heady = chiefPosition.y + 25;
        float Headx = chiefPosition.x + 50;

        DrawCircle(Headx, Heady, headR, WHITE);

        float crownX = Headx - 25;
        float crownY = chiefPosition.y + 5;

        DrawRectangle(crownX, crownY, 50, 10, GOLD);

        float spikeW = 10, spikeH = 12;
        for (int i = 0; i < 3; ++i)
        {
            float sx = crownX + spikeW * (2 * i);
            DrawTriangle({ sx, crownY },
                { sx + spikeW, crownY },
                { sx + spikeW * 0.5f, crownY - spikeH },
                GOLD);
        }

        const Color BELT_CLR = GOLD;
        const Color BOOT_CLR = DARKBROWN;

        float bodyW = 40, bodyH = 50;
        float bodyX = crownX + 5, bodyY = crownY + 35;
        DrawRectangle(bodyX, bodyY, bodyW, bodyH, BLACK);

        float beltH = bodyH * 0.14f;
        DrawRectangle(bodyX, bodyY + bodyH * 0.45f, bodyW, beltH, BELT_CLR);

        float armW = gridSize * 0.12f, armH = gridSize * 0.30f;
        float armY = bodyY + bodyH * 0.15f;

        DrawRectangle(bodyX - armW, armY, armW, armH, BLACK);
        DrawRectangle(bodyX + bodyW, armY, armW, armH, BLACK);

        float legW = gridSize * 0.12f, legH = gridSize * 0.28f;
        float legY = bodyY + bodyH;

        DrawRectangle(bodyX + bodyW * 0.15f, legY, legW, legH, BOOT_CLR);
        DrawRectangle(bodyX + bodyW * 0.73f, legY, legW, legH, BOOT_CLR);

        float swordHandleX = bodyX + bodyW + armW * 0.5f;
        float swordHandleY = armY - gridSize * 0.04f;
        float handleH = gridSize * 0.10f;
        float bladeH = gridSize * 0.50f;
        float bladeW = 4.0f;

        DrawRectangle(swordHandleX - bladeW * 0.5f,
            swordHandleY,
            bladeW,
            handleH,
            BROWN);

        DrawRectangle(swordHandleX - 10,
            swordHandleY,
            20,
            3,
            GOLD);

        DrawRectangle(swordHandleX - bladeW * 0.5f,
            swordHandleY - bladeH,
            bladeW,
            bladeH,
            LIGHTGRAY);

        DrawCircle(swordHandleX, swordHandleY + handleH, 3, GOLD);
    }
    void pixelCheif() {
        //if (kingSkin = DEFAULT) {
        int chiefx = chiefPosition.x;
        int chiefy = chiefPosition.y;
        Image chiefimage = LoadImage("kingc2.PNG");
        Texture2D chieftex = LoadTextureFromImage(chiefimage); // Convert image to texture
        UnloadImage(chiefimage);  // We no longer need the image after converting it to a texture
        DrawTexture(chieftex, chiefx, chiefy, WHITE);
        /*}*/

        //if (kingSkin = SKIN1) {
        //    int chiefx = chiefPosition.x;
        //    int chiefy = chiefPosition.y;
        //    Image chiefimage = LoadImage("kingccrop.PNG");
        //    Texture2D chieftex = LoadTextureFromImage(chiefimage); // Convert image to texture
        //    UnloadImage(chiefimage);  // We no longer need the image after converting it to a texture
        //    DrawTexture(chieftex, chiefx, chiefy, WHITE);           

        //}
        //if (kingSkin = SKIN2) {
        //    int chiefx = chiefPosition.x;
        //    int chiefy = chiefPosition.y;
        //    Image chiefimage = LoadImage("chachu400.PNG");
        //    Texture2D chieftex = LoadTextureFromImage(chiefimage); // Convert image to texture
        //    UnloadImage(chiefimage);  // We no longer need the image after converting it to a texture
        //    DrawTexture(chieftex, chiefx, chiefy, WHITE);          
        //}
    }
    void DrawChief() {


        float headR = gridSize * 0.18;
        float Heady = chiefPosition.y + 25;
        float Headx = chiefPosition.x + 50;

        DrawCircle(Headx, Heady, headR, WHITE);

        float crownX = Headx - 25;
        float crownY = chiefPosition.y + 5;

        DrawRectangle(crownX, crownY, 50, 10, GOLD);

        float spikeW = 10;
        float spikeH = 12;
        for (int i = 0; i < 3; ++i)
        {
            // sx check 
            float sx = crownX + spikeW * (2 * i);
            DrawTriangle({ sx,crownY }, { sx + spikeW,crownY }, { sx + spikeW * 0.5f, crownY - spikeH }, GOLD);
        }


        float bodyW = 40;
        float bodyH = 50;
        float bodyX = crownX + 5;
        float bodyY = crownY + 35;
        DrawRectangle(bodyX, bodyY, bodyW, bodyH, RED);

        float beltH = bodyH * 0.14;
        DrawRectangle(bodyX, bodyY + bodyH * 0.45, bodyW, beltH, BROWN);


        float armW = gridSize * 0.12;
        float armH = gridSize * 0.30;
        float armY = bodyY + bodyH * 0.15;

        DrawRectangle(bodyX - armW, armY, armW, armH, RED);
        DrawRectangle(bodyX + bodyW, armY, armW, armH, RED);


        float legW = gridSize * 0.12;
        float legH = gridSize * 0.28;
        float legY = bodyY + bodyH;

        DrawRectangle(bodyX + bodyW * 0.15, legY, legW, legH, DARKBROWN);
        DrawRectangle(bodyX + bodyW * 0.73, legY, legW, legH, DARKBROWN);


        float sceptreX1 = bodyX + bodyW + armW * 0.5;
        float sceptreY1 = armY - gridSize * 0.10;
        float sceptreY2 = sceptreY1 + gridSize * 0.65;
        DrawLineEx({ sceptreX1, sceptreY1 }, { sceptreX1, sceptreY2 }, 4, GOLD);
        DrawCircle(sceptreX1, sceptreY1, 6, YELLOW);

    }
    void background() {
        for (int y = 0; y < screenHeight; y++) {
            DrawLine(0, y, screenWidth, y, GRAY);
        }
    }
    RenderSystem() {}

    // initialization of the builind dimensions / name / color 
    // Chief starting position
    // population military leadership initialization
    // Update the Init method to initialize the new kingdom chief position
    void Init() {
        screenWidth = 1200;
        screenHeight = 700;
        gridSize = 100; // size of each block
        InitWindow(screenWidth, screenHeight, "Stronghold");
        SetTargetFPS(60);

        // Chief starting position
        chiefPosition = { 1000, 500, (float)gridSize, (float)gridSize };

        // Initialize new kingdom chief position
        newKingdomChiefPosition = { 500, 400, (float)gridSize, (float)gridSize };

        // Initialize the new kingdom buildings
        InitNewKingdomBuildings();

        // Rest of your initialization code...
        buildingCount = 7;
        const int x = 10;
        const int y = 4;

        // initialization of the builind dimensions / name / color 
        buildings[0] = { "Castle",
            {(float)(x * gridSize - 50), // rect.x
            (float)(y * gridSize - 100),  //rect.y
            (float)gridSize,
            (float)gridSize},
            DARKGRAY };

        buildings[1] = { "Barracks", {(float)((4) * gridSize), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, RED };
        buildings[2] = { "Market", {(float)((650)), (float)((550)), (float)gridSize, (float)gridSize}, ORANGE };
        //buildings[3] = { "Granary", {(float)((x - 1) * gridSize - 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, RED };
        //buildings[4] = { "Town Hall", {(float)((x + 1) * gridSize + 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, BLUE };
        buildings[5] = { "Blacksmith", {(float)(450), (float)((200)), (float)gridSize, (float)gridSize}, BROWN };
        buildings[6] = { "Church", {(float)(750), (float)((250)), (float)gridSize, (float)gridSize}, PURPLE };
        buildings[7] = { "new", {(50), 200, (float)gridSize, (float)gridSize}, RED };

        population = Population(500, 70, 100);
        military = Military(200, 80, 100, 10, 1000, 50);
        leadership = Leadership();

        std::srand(std::time(nullptr));
    }

    // Update the destructor to clean up resources
    ~RenderSystem() {
        UnloadNewKingdomChiefTexture();
    }
    // notice board window
    void DrawSideWindow() {
        int sideWindowWidth = 600;
        int sideWindowHeight = screenHeight; //700
        int sideWindowX = 0;
        int sideWindowY = 0;

        DrawRectangle(sideWindowX, sideWindowY, sideWindowWidth, sideWindowHeight, DARKGRAY);

        DrawText("Notices", sideWindowX + 10, sideWindowY + 10, 20, WHITE);


    }

    void pixelbackground() {
        int sideWindowX = 0;
        int sideWindowY = 0;

        int chiefx = 0;
        int chiefy = 0;
        Image chiefimage = LoadImage("village.JPG");
        Texture2D chieftex = LoadTextureFromImage(chiefimage); // Convert image to texture
        UnloadImage(chiefimage);  // We no longer need the image after converting it to a texture
        DrawTexture(chieftex, chiefx, chiefy, WHITE);


    }


    void pixelbackground2() {
        int sideWindowX = 0;
        int sideWindowY = 0;
        int chiefx = 100;
        int chiefy = 0;
        Image chiefimage = LoadImage("village4.PNG");
        Texture2D chieftex = LoadTextureFromImage(chiefimage); // Convert image to texture
        UnloadImage(chiefimage);  // We no longer need the image after converting it to a texture
        DrawTexture(chieftex, chiefx, chiefy, WHITE);
    }

    void castlemenue()
    {
        //Drwa Castle Menu
        DrawText("Castle Menu", 20, 530, 20, RED);
        DrawText("1. Soldiers Salaries (1 gold /1 soldier)", 20, 555, 20, BLACK);
        DrawText("2. display leadership", 20, 580, 20, BLACK);
        DrawText("3. Display King's Policies", 20, 605, 20, BLACK);

        if (IsKeyPressed(KEY_ONE))
        {
            if (kingdom.economy.gold >= military.soldiers)
            {
                kingdom.economy.gold -= military.soldiers;
                kingdom.events.add("Executed: Soldiers salaries have been paid.");
            }
            else
            {
                kingdom.events.add(" Not enough gold to pay salaries.");
                military.soldiers -= military.soldiers - kingdom.economy.gold;
                kingdom.peasants.population += military.soldiers - kingdom.economy.gold;
                kingdom.economy.gold -= military.soldiers - kingdom.economy.gold;
                military.morale -= 3;
                kingdom.nobles.unrest -= 3;
            }
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            leadership.DisplayLeadership();

        }
        else if (IsKeyPressed(KEY_THREE))
        {
            leadership.DisplayLeadershipPolicies();

        }


    }

    void barrackmenue()
    {
        //Draw Barrack Menu
        DrawText("Barrack Menu", 20, 530, 20, RED);
        DrawText("1. Train Troops (10 gold / 10 soldiers)", 20, 555, 20, BLACK);
        DrawText("2. Get Equipment (10 gold / 15 arrows)", 20, 580, 20, BLACK);
        DrawText("3. Recruit soldier (10 gold / 10 soldiers)", 20, 605, 20, BLACK);
        DrawText("4. Inventory Display ", 20, 625, 20, BLACK);

        if (IsKeyPressed(KEY_ONE))
        {
            if (kingdom.economy.gold >= military.soldiers)
            {
                kingdom.economy.gold -= military.soldiers;
                kingdom.events.add(" Executed: Soldiers training successful.");
            }
            else
            {
                kingdom.events.add(" Not enough gold to train the soldiers.");
                military.morale -= 5;
            }
        }

        //else if (IsKeyPressed(KEY_TWO))
        //{
        //    //BUY EQUIPMENT
        //}

        else if (IsKeyPressed(KEY_THREE))
        {

            int recruits = 0;
            if (kingdom.warChance > 50) {
                recruits = kingdom.peasants.population / 5;
                military.soldiers += recruits;
                kingdom.events.add(" Executed: soldiers added to Military.");
                // cout << " Executed: " << recruits << " soldiers added to Military.\n";
            }
            else {
                kingdom.events.add("Not enough population to recruit soldiers.");
            }
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            military.displayinventory();
        }

    }

    void blacksmithmenue()
    {
        //Draw Blacksmith Menu
        DrawText("Blacksmith Menu", 20, 530, 20, RED);
        DrawText("1. Forge Swords (10 iron / 5 swords)", 20, 555, 20, BLACK);
        DrawText("2. Forge Arrows (10 wood / 5 arrows)", 20, 580, 20, BLACK);
        DrawText("3. Forge Armours (10 iron /  2 Armours)", 20, 605, 20, BLACK);

        if (IsKeyPressed(KEY_ONE))
        {
            if (kingdom.resources.iron >= 10)
            {
                kingdom.resources.iron -= 10;
                military.swords += 5;
                kingdom.events.add("Executed: Swords forged successfully.");
            }

        }
        else if (IsKeyPressed(KEY_TWO))
        {
            if (kingdom.resources.wood >= 10)
            {
                kingdom.resources.wood -= 10;
                military.arrows += 5;
                kingdom.events.add(" Executed: Arrows forged successfully.");
            }
            else
            {
                kingdom.events.add(" Not enough wood to forge Arrows.");
            }
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            if (kingdom.resources.iron >= 10)
            {
                kingdom.resources.iron -= 10;
                military.armours = 2;
                kingdom.events.add(" Executed: armour forged successfully.");
            }
            else
            {
                kingdom.events.add("Not enough iron to forge armour.");
            }
        }


    }

    void churchmenue()
    {
        //Draw Church Menu
        DrawText("Church Menu", 20, 530, 20, RED);
        DrawText("1. Noble Meeting (unrest -= 5)", 20, 555, 20, BLACK);
        DrawText("2. War negotiations (morale += 10)", 20, 580, 20, BLACK);
        DrawText("3. Worship (unrest -= 2 && morale += 5)", 20, 605, 20, BLACK);

        if (IsKeyPressed(KEY_ONE))
        {
            if (leadership.approvalRating < 50)
            {
                leadership.approvalRating += 10;
                kingdom.nobles.unrest -= 10;
                kingdom.peasants.unrest -= 10;
                kingdom.merchants.unrest -= 10;
            }
            else
            {
                kingdom.events.add("No need for Noble Meeting.");
            }
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            if (kingdom.warChance > 50)
            {
                kingdom.events.add("Executed: Bought 10 food for 10 gold");
                cout << "War Negotiations under way \n";
                if (rand() % 4 == 4)
                {
                    kingdom.events.add("Negotiations unsuccessful!");
                    leadership.approvalRating -= 10;
                    kingdom.nobles.unrest += 10;
                    kingdom.peasants.unrest += 10;
                    kingdom.merchants.unrest += 10;
                }
                else
                {
                    kingdom.events.add("Negotiations successful");
                    leadership.approvalRating += 10;
                    kingdom.nobles.unrest -= 10;
                    kingdom.peasants.unrest -= 10;
                    kingdom.merchants.unrest -= 10;
                }
            }
            else {
                kingdom.events.add(" No War Negotiations in progress");
            }
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            leadership.approvalRating += 2;
            kingdom.nobles.unrest -= 3;
            kingdom.peasants.unrest -= 3;
            kingdom.merchants.unrest -= 3;
            military.morale += 5;
        }

    }

    void marketmenue() {
        // Draw Market Menu
        DrawText("Market Menu", 20, 530, 20, RED);
        DrawText("1. Buy Food (10 gold / 10 food)", 20, 555, 20, BLACK);
        DrawText("2. Trade Wood for Food (10 wood / 10 food)", 20, 580, 20, BLACK);
        DrawText("3. Trade Iron for Gold ", 20, 605, 20, BLACK);

        if (IsKeyPressed(KEY_ONE)) {
            if (kingdom.economy.gold >= 10) {
                kingdom.economy.gold -= 10;
                kingdom.resources.food += 10;
                //messagemenue = "Executed: Bought 10 food for 10 gold";
                kingdom.events.add("Executed: Bought 10 food for 10 gold");
            }
            else {
                messagemenue = "Not enough gold to buy food";
                kingdom.events.add(messagemenue.c_str());
            }
        }
        else if (IsKeyPressed(KEY_TWO)) {
            int trade_wood = 10;
            if (kingdom.resources.wood >= trade_wood) {
                int food_gained = 10;
                if (kingdom.resources.food < kingdom.resources.wood) {
                    food_gained = 20;
                }
                else if (kingdom.resources.wood < kingdom.resources.food) {
                    food_gained = 5;
                }
                kingdom.resources.wood -= trade_wood;
                kingdom.resources.food += food_gained;
                messagemenue = "  Executed: Traded " + to_string(trade_wood) + " wood for " + to_string(food_gained) + " food";
                kingdom.events.add(messagemenue.c_str());
            }
            else {
                messagemenue = "  Not enough wood to trade for food";
                kingdom.events.add(messagemenue.c_str());
            }
        }
        else if (IsKeyPressed(KEY_THREE)) {
            int trade_iron = 10;
            if (kingdom.resources.iron >= trade_iron) {
                int gold_gained = 10;
                if (kingdom.economy.gold < kingdom.resources.iron) {
                    gold_gained = 20;
                }
                else if (kingdom.resources.iron < kingdom.economy.gold) {
                    gold_gained = 5;
                }
                kingdom.resources.iron -= trade_iron;
                kingdom.economy.gold += gold_gained;
                messagemenue = " Executed: Traded " + to_string(trade_iron) + " iron for " + to_string(gold_gained) + " gold";
                kingdom.events.add(messagemenue.c_str());
            }
            else {
                messagemenue = " Not enough iron to trade for gold";
                kingdom.events.add(messagemenue.c_str());
            }
        }


    }
    void addNewKingdom() {
        Kingdom newKingdom;
        // Use string concatenation method compatible with C++
        char clanNumber[10];
        _itoa_s(additionalKingdoms.size() + 1, clanNumber, 10);

        // Customize the new kingdom's initial stats differently from the main kingdom
        newKingdom.peasants.name = (string("Clan ") + clanNumber + " Peasants").c_str();
        newKingdom.peasants.population = 250 + (additionalKingdoms.size() * 50);
        newKingdom.peasants.unrest = 10.0 + (additionalKingdoms.size() * 2.0f);

        newKingdom.merchants.name = (string("Clan ") + clanNumber + " Merchants").c_str();
        newKingdom.merchants.population = 50 + (additionalKingdoms.size() * 10);
        newKingdom.merchants.unrest = 5.0 + (additionalKingdoms.size() * 1.0f);

        newKingdom.nobles.name = (string("Clan ") + clanNumber + " Nobles").c_str();
        newKingdom.nobles.population = 15 + (additionalKingdoms.size() * 3);
        newKingdom.nobles.unrest = 2.0 + (additionalKingdoms.size() * 0.5f);

        newKingdom.leader.title = "Clan Chief";

        char leaderNumber[10];
        _itoa_s(additionalKingdoms.size() + 1, leaderNumber, 10);
        newKingdom.leader.name = (string("Rashid ") + leaderNumber).c_str();

        newKingdom.leader.age = 35 + (additionalKingdoms.size() * 2);
        newKingdom.leader.approvalRating = 70 - (additionalKingdoms.size() * 5);
        newKingdom.leader.style = static_cast<LeadershipStyle>(additionalKingdoms.size() % 3);

        newKingdom.army.soldiers = 50 + (additionalKingdoms.size() * 10);
        newKingdom.army.training = 40.0 + (additionalKingdoms.size() * 5.0f);
        newKingdom.army.morale = 75.0 - (additionalKingdoms.size() * 5.0f);
        newKingdom.army.corruption = 0.2 + (additionalKingdoms.size() * 0.1f);

        newKingdom.economy.gold = 250.0 + (additionalKingdoms.size() * 50.0f);
        newKingdom.economy.debt = 0.0;
        newKingdom.economy.taxRate = 0.8 - (additionalKingdoms.size() * 0.1f);
        newKingdom.economy.inflation = 0.1 + (additionalKingdoms.size() * 0.05f);
        newKingdom.economy.interestRate = 0.03 + (additionalKingdoms.size() * 0.01f);
        newKingdom.economy.corruption = 0.2 + (additionalKingdoms.size() * 0.1f);

        newKingdom.resources.food = 150 + (additionalKingdoms.size() * 30);
        newKingdom.resources.wood = 100 + (additionalKingdoms.size() * 20);
        newKingdom.resources.stone = 30 + (additionalKingdoms.size() * 5);
        newKingdom.resources.iron = 80 + (additionalKingdoms.size() * 15);

        additionalKingdoms.push_back(newKingdom);
        currentKingdomIndex = additionalKingdoms.size() - 1;
    }
    void newwindow() {
        if (additionalKingdoms.empty()) {
            addNewKingdom();
        }

        // Initialize new kingdom chief position if not set
        if (newKingdomChiefPosition.width == 0) {
            newKingdomChiefPosition = { 500, 400, (float)gridSize, (float)gridSize };
        }

        // Load the texture once before entering the loop
        LoadNewKingdomChiefTexture();

        // Ensure currentKingdomIndex is valid
        if (currentKingdomIndex < 0 || currentKingdomIndex >= additionalKingdoms.size()) {
            currentKingdomIndex = 0;
        }

        bool inNewKingdomWindow = true;

        while (inNewKingdomWindow && !WindowShouldClose()) {
            // Check for escape key at the beginning of each loop iteration
            if (IsKeyPressed(KEY_ESCAPE)) {
                inNewKingdomWindow = false;
                continue; // Skip to next iteration to exit loop
            }

            // Initialize buildings for the new kingdom
            InitNewKingdomBuildings();

            // Update chief movement
            UpdateNewKingdomChiefMovement();

            // Clan switching
            if (IsKeyPressed(KEY_TAB)) {
                if (IsKeyDown(KEY_LEFT_SHIFT)) {
                    // Previous clan (move backwards)
                    currentKingdomIndex = (currentKingdomIndex - 1 + additionalKingdoms.size()) % additionalKingdoms.size();
                }
                else {
                    // Next clan (move forwards)
                    currentKingdomIndex = (currentKingdomIndex + 1) % additionalKingdoms.size();
                }
            }

            // Ensure currentKingdomIndex is valid
            if (currentKingdomIndex < 0 || currentKingdomIndex >= additionalKingdoms.size()) {
                currentKingdomIndex = 0;
            }

            Kingdom& currentKingdom = additionalKingdoms[currentKingdomIndex];

            BeginDrawing();
            ClearBackground(BLACK);

            pixelbackground2();

            // Draw the buildings for the new kingdom
            DrawNewKingdomBuildings();

            // Draw the chief in the new kingdom
            if (newKingdomChiefTextureLoaded) {
                DrawTexture(newKingdomChiefTexture, newKingdomChiefPosition.x, newKingdomChiefPosition.y, WHITE);
            }
            else {
                // Fallback if texture not loaded
                DrawRectangleRec(newKingdomChiefPosition, RED);
            }

            // Handle building interactions
            HandleNewKingdomBuildingInteractions(currentKingdom);

            // Display new kingdom stats
            char msg[128];
            DrawText("New Clan Population:", 10, 50, 18, GREEN);

            sprintf_s(msg, sizeof(msg), "Peasants: %d", currentKingdom.peasants.population);
            DrawText(msg, 30, 70, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Merchants: %d", currentKingdom.merchants.population);
            DrawText(msg, 30, 90, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Nobles: %d", currentKingdom.nobles.population);
            DrawText(msg, 30, 110, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Unrest - Peasants: %d%%, Merchants: %d%%, Nobles: %d%%",
                static_cast<int>(currentKingdom.peasants.unrest),
                static_cast<int>(currentKingdom.merchants.unrest),
                static_cast<int>(currentKingdom.nobles.unrest));
            DrawText(msg, 30, 130, 16, (currentKingdom.peasants.unrest > 50 ||
                currentKingdom.merchants.unrest > 50 ||
                currentKingdom.nobles.unrest > 50) ? RED : YELLOW);

            DrawText("Resources:", 10, 170, 18, GREEN);

            sprintf_s(msg, sizeof(msg), "Food: %d", currentKingdom.resources.food);
            DrawText(msg, 30, 190, 18, (currentKingdom.resources.food < (currentKingdom.peasants.population +
                currentKingdom.merchants.population +
                currentKingdom.nobles.population)) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Wood: %d", currentKingdom.resources.wood);
            DrawText(msg, 150, 190, 18, (currentKingdom.resources.wood < (int)((currentKingdom.peasants.population +
                currentKingdom.merchants.population +
                currentKingdom.nobles.population) * 0.1f)) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Stone: %d", currentKingdom.resources.stone);
            DrawText(msg, 270, 190, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Iron: %d", currentKingdom.resources.iron);
            DrawText(msg, 390, 190, 18, (currentKingdom.resources.iron < currentKingdom.army.soldiers * 1) ? RED : YELLOW);

            DrawText("Economy:", 10, 230, 18, GREEN);

            sprintf_s(msg, sizeof(msg), "Gold: %d", static_cast<int>(currentKingdom.economy.gold));
            DrawText(msg, 30, 250, 18, (currentKingdom.economy.gold < 20.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Debt: %d", static_cast<int>(currentKingdom.economy.debt));
            DrawText(msg, 150, 250, 18, (currentKingdom.economy.debt > 0.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Tax Rate: %d%%", static_cast<int>(currentKingdom.economy.taxRate * 100));
            DrawText(msg, 30, 270, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Inflation: %d%%", static_cast<int>(currentKingdom.economy.inflation * 100));
            DrawText(msg, 200, 270, 18, (currentKingdom.economy.inflation > 0.3f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Corruption: %d%%", static_cast<int>(currentKingdom.economy.corruption * 100));
            DrawText(msg, 370, 270, 18, (currentKingdom.economy.corruption > 0.5f) ? RED : YELLOW);

            DrawText("Military:", 10, 310, 18, GREEN);

            sprintf_s(msg, sizeof(msg), "Soldiers: %d", currentKingdom.army.soldiers);
            DrawText(msg, 30, 330, 18, (currentKingdom.army.soldiers == 0) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Training: %d%%", static_cast<int>(currentKingdom.army.training));
            DrawText(msg, 150, 330, 18, (currentKingdom.army.training < 30.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Morale: %d%%", static_cast<int>(currentKingdom.army.morale));
            DrawText(msg, 300, 330, 18, (currentKingdom.army.morale > 50.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Army Corruption: %d%%", static_cast<int>(currentKingdom.army.corruption * 100));
            DrawText(msg, 30, 350, 18, (currentKingdom.army.corruption > 0.3f) ? RED : YELLOW);

            // Add control instructions
            DrawText("Use arrow keys to move chief", 30, 400, 18, WHITE);
            DrawText("Press ESC to return to main kingdom", 30, 430, 18, WHITE);

            // Display event log for the new kingdom
            DrawText("Recent Events:", 800, 50, 18, GREEN);
            int evCount = currentKingdom.events.count;
            for (int i = 0; i < evCount; ++i) {
                DrawText(currentKingdom.events.messages[i], 820, 70 + 20 * i, 16, GOLD);
            }
            if (evCount == 0) {
                DrawText("No events yet.", 820, 70, 16, GOLD);
            }

            // Display clan selection controls if there are multiple clans
            if (additionalKingdoms.size() > 1) {
                DrawText("PRESS TAB/TAB+SHIFT TO SWITCH BETWEEN CLANS", 800, 580, 16, WHITE);

                // Display current clan number
                char clanMsg[64];
                sprintf_s(clanMsg, sizeof(clanMsg), "Current Clan: %d of %d",
                    currentKingdomIndex + 1,
                    (int)additionalKingdoms.size());
                DrawText(clanMsg, 800, 610, 18, GOLD);
            }

            // Handle day advancement
            if (IsKeyPressed(KEY_SPACE)) {
                currentKingdom.updateday();
                char dayMsg[128];
                sprintf_s(dayMsg, sizeof(dayMsg), "Day %d passed", currentKingdom.day);
                currentKingdom.addEvent(dayMsg);
            }

            EndDrawing();
        }
    }
    void newclan() {
        // Don't call BeginDrawing/EndDrawing here - should be handled by the main loop
        DrawText("Press ENTER to add a new clan", 20, 530, 20, RED);

        // Check for ENTER key
        if (IsKeyPressed(KEY_ENTER)) {
            newwindow(); // The function will handle its own loop
        }
    }

    void  Run() {

        int selectedOption = 0;
        while (!WindowShouldClose()) {

            if (IsKeyPressed(KEY_SPACE)) {
                //kingdom.AIControl();
                kingdom.updateday();
            }
            UpdateChiefMovement();

            BeginDrawing();
            //ClearBackground(SKYBLUE);
            background();
            //DrawGrid();
            pixelbackground();
            //ClearBackground(BLACK);
            //pixelbackground2();
            //DrawBuildings();
            //DrawChief2();
            pixelCheif();
            Drawdiscription();
            //DrawSideWindow();

            ClearBackground(RAYWHITE);

            // Prepare some colors for different texts
            Color titleColor = GREEN;
            Color statColor = GOLD;
            Color goodColor = DARKGREEN;

            // display the day on the middle of the screen

            // using _itoa to convert integer into string
            // add then passing the string to the draw text function

            char msg[128];

            DrawText("population:", 10, 50, 18, titleColor);

            sprintf_s(msg, sizeof(msg), "Peasants: ");
            _itoa_s(kingdom.peasants.population, msg + strlen(msg), sizeof(msg) - strlen(msg), 10); // Convert integer to string and append
            DrawText(msg, 30, 70, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Merchants: ");
            _itoa_s(kingdom.merchants.population, msg + strlen(msg), sizeof(msg) - strlen(msg), 10); // Convert integer to string and append
            DrawText(msg, 30, 90, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "nobles: ");
            _itoa_s(kingdom.nobles.population, msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 30, 110, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "unrest - Peasants: ");
            _itoa_s(static_cast<int>(kingdom.peasants.unrest), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "%, Merchants: ");
            _itoa_s(static_cast<int>(kingdom.merchants.unrest), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "% ,Nobles: ");
            _itoa_s(static_cast<int>(kingdom.nobles.unrest), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), " % ");
            DrawText(msg, 30, 130, 16, (kingdom.peasants.unrest > 50 || kingdom.merchants.unrest > 50 || kingdom.nobles.unrest > 50) ? RED : YELLOW);

            DrawText("resource:", 10, 170, 18, titleColor);

            sprintf_s(msg, sizeof(msg), "food: ");
            _itoa_s(kingdom.resources.food, msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 30, 190, 18, (kingdom.resources.food < (kingdom.peasants.population + kingdom.merchants.population + kingdom.nobles.population)) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Wood: ");
            _itoa_s(kingdom.resources.wood, msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 150, 190, 18, (kingdom.resources.wood < (int)((kingdom.peasants.population + kingdom.merchants.population + kingdom.nobles.population) * 0.1f)) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Stone: ");
            _itoa_s(kingdom.resources.stone, msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 270, 190, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Iron: ");
            _itoa_s(kingdom.resources.iron, msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 390, 190, 18, (kingdom.resources.iron < kingdom.army.soldiers * 1) ? RED : YELLOW);

            DrawText("eco::", 10, 230, 18, titleColor);

            sprintf_s(msg, sizeof(msg), "Gold: ");
            _itoa_s(static_cast<int>(kingdom.economy.gold), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 30, 250, 18, (kingdom.economy.gold < 20.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Debt: ");
            _itoa_s(static_cast<int>(kingdom.economy.debt), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 150, 250, 18, (kingdom.economy.debt > 0.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Tax Rate: ");
            _itoa_s(static_cast<int>(kingdom.economy.taxRate * 100), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "%");
            DrawText(msg, 30, 270, 18, YELLOW);

            sprintf_s(msg, sizeof(msg), "Inflation: ");
            _itoa_s(static_cast<int>(kingdom.economy.inflation * 100), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "%");
            DrawText(msg, 200, 270, 18, (kingdom.economy.inflation > 0.3f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "corruption: ");
            _itoa_s(static_cast<int>(kingdom.economy.corruption * 100), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "%");
            DrawText(msg, 370, 270, 18, (kingdom.economy.corruption > 0.5f) ? RED : YELLOW);

            DrawText("Military:", 10, 310, 18, titleColor);

            sprintf_s(msg, sizeof(msg), "Soldiers: ");
            _itoa_s(kingdom.army.soldiers, msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            DrawText(msg, 30, 330, 18, (kingdom.army.soldiers == 0) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "training: ");
            _itoa_s(static_cast<int>(kingdom.army.training), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "%");
            DrawText(msg, 150, 330, 18, (kingdom.army.training < 30.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Morale: ");
            _itoa_s(static_cast<int>(kingdom.army.morale), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "%");
            DrawText(msg, 300, 330, 18, (kingdom.army.morale > 50.0f) ? RED : YELLOW);

            sprintf_s(msg, sizeof(msg), "Army Corruption: ");
            _itoa_s(static_cast<int>(kingdom.army.corruption * 100), msg + strlen(msg), sizeof(msg) - strlen(msg), 10);
            strcat_s(msg, sizeof(msg), "%");
            DrawText(msg, 30, 350, 18, (kingdom.army.corruption > 0.3f) ? RED : YELLOW);


            // checking the collision of the charcter with tje buildings and displaying the menue
            if (CheckCollisionRecs(chiefPosition, buildings[0].rect)) {
                castlemenue();
            }

            if (CheckCollisionRecs(chiefPosition, buildings[1].rect)) {

                barrackmenue();
            }
            if (CheckCollisionRecs(chiefPosition, buildings[5].rect)) {

                blacksmithmenue();

            }
            if (CheckCollisionRecs(chiefPosition, buildings[6].rect)) {
                churchmenue();
            }

            if (CheckCollisionRecs(chiefPosition, buildings[2].rect)) {

                marketmenue();
            }
            if (CheckCollisionRecs(chiefPosition, buildings[7].rect)) {

                newclan();
            }
            // displaying the event log 

            DrawText("Recent Events:", 10, 390, 18, titleColor);
            int evCount = kingdom.events.count;
            for (int i = 0; i < evCount; ++i) {
                DrawText(kingdom.events.messages[i], 30, 410 + 20 * i, 16, statColor);
            }
            if (evCount == 0) {
                DrawText("No events yet.", 30, 410, 16, statColor);
            }

            DrawText("PRESS SPACE FOR NEXT DAY", 500, 670, 20, BLACK);




            EndDrawing();
        }
        CloseWindow();
    }

};


int main()
{
    RenderSystem renderer;
    renderer.Init();
    renderer.MainMenu();
    renderer.SelectKingSkin();
    renderer.Run();
    return 0;
}
