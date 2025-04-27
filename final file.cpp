// ﻿#include "raylib.h"
// #include <string>
// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// using namespace std;
// class Resources {
// public:
//    int food = 1000;
//    int wood;
//    int stone;
//    int iron;

//    Resources() : food(0), wood(0), stone(0), iron(0) {}
// };
// struct Economy {
//    float gold;
//    float debt;         // when the gold gets less than zero
//    float taxRate;
//    float inflation;
//    float interestRate;
//    float corruption;

//    Economy() : gold(0.0f), debt(0.0f), taxRate(1.0f), inflation(0.0f), interestRate(0.05f), corruption(0.0f) {}
// };

// // this will devide the population into segments like peasents merchants and nobels
// struct SocialClass {
//    const char* name;
//    int population;
//    float unrest;

//    SocialClass() : name(""), population(0), unrest(0.0f) {}
// };

// class Population :public Resources {
// public:
//    int currentPopulation;
//    int employmentRate;

//    Population() {}
//    Population(int initialPopulation, int employmentRate, int wealth)
//        : currentPopulation(initialPopulation), employmentRate(employmentRate) {}

//    // replicating the effects of resources on population
//    void UpdatePopulation() {
//        if (food < 50) {
//            currentPopulation -= 5;
//        }
//        else if (employmentRate > 80) {
//            currentPopulation += 10;
//        }
//    }

//    void DisplayPopulation(int x, int y) {
//        string populationData = "Population: " + std::to_string(currentPopulation) +
//            "\nFood Supply: " + to_string(food) +
//            "\nEmployment Rate: " + to_string(employmentRate);

//        DrawText(populationData.c_str(), x, y, 20, WHITE);
//    }


// };

// class Military : public Resources {
// public:
//    int soldiers;
//    int morale;
//    float training; // percentage of training skills
//    int pay;
//    int corruption;
//    int costToTrain = 10;
//    int trainCoins;
//    string message;

//    Military() : message("") {}
//    Military(int soldiersCount, int morale, int pay, int corruption, int trainCoins, int training)
//        :training(training), trainCoins(trainCoins), soldiers(soldiersCount), morale(morale), pay(pay), corruption(corruption) {}

//    void Recruit(int population, int x, int y) {
//        // recruit 10 percent of the population on call
//        int newSoldiers = population / 10;
//        soldiers += newSoldiers;
//        message = "Recruited " + to_string(newSoldiers) + " soldiers!";
//        if (!message.empty()) {
//            DrawText(message.c_str(), x, y, 20, YELLOW);
//        }
//    }

//    void TrainSoldiers(int number, int x, int y) {
//        if (trainCoins > (number * costToTrain)) {
//            morale += 10;
//            training += 10;
//            pay += 10;
//            trainCoins -= (number * costToTrain);
//            message = "Training..Morale increased";
//        }
//        else {
//            message = "Not enough resources ";
//        }
//        if (!message.empty()) {
//            DrawText(message.c_str(), x, y, 20, RED);
//        }
//    }

//    void UpdateMilitary() {
//        if (food < 50) {
//            morale -= 10;
//        }

//        if (pay < 50) {
//            morale -= 15;
//        }

//        if (morale < 50) {
//           soldiers -= 5;
//        }

//        if (corruption > 50) {
//            morale -= 20;
//            std::cout << "Corruption is high, morale is decreasing" << endl;
//        }
//    }

//    void DisplayMilitary(int x, int y) {
//        std::string militaryData = "Soldiers: " + to_string(soldiers) +
//            "\nMorale: " + to_string(morale) + "%" +
//            "\nPay: " + to_string(pay) +
//            "\nCorruption: " + to_string(corruption) + "%";

//        DrawText(militaryData.c_str(), x, y, 20, WHITE);
//    }


//    void IncreaseCorruption() {
//        corruption += 5;  // Corruption increases over time
//    }
// };

// class Leadership {
// public:
//    string title;
//    int approvalRating;
//    bool isAlive;
//    int age;
//    string message;

//    // initialize X and Y with the best cordinates to dsiplay
//    int x;
//    int y;
//    Leadership() : isAlive(true), message("") {}
//    Leadership(int approvalRating) : approvalRating(approvalRating), isAlive(true), message("") {}

//    void UpdateLeadership(int change) {
//        approvalRating += change;
//        if (approvalRating < 0) approvalRating = 0;
//        if (approvalRating > 100) approvalRating = 100;
//        message = "the approval raiting is increased";
//        DrawText(message.c_str(), x, y, 20, WHITE);
//    }

//    void DisplayLeadership(int x, int y) {
//        string leadershipData = "Leadership Approval: " + to_string(approvalRating) + "%";
//        DrawText(leadershipData.c_str(), x, y, 20, WHITE);


//    }
//    // when the approval rating drop 

//    void Election() {
//        if (approvalRating < 30) {
//            message = "The leadership is weak. An election will take place!";
//            isAlive = false;
//        }
//        else {
//            message = "the leadership have the majority";
//        }
//        if (!message.empty()) {
//            DrawText(message.c_str(), x, y, 20, YELLOW);
//        }
//    }
//    // when the leader is not alive 
//    void militaryRaj() {
//        if (!isAlive) {
//            message = "military Raj has occurred";
//        }
//        else {
//            message = "No coupe";
//        }
//        DrawText(message.c_str(), x, y, 20, YELLOW);

//    }

//    void margya() {
//        if (isAlive && approvalRating < 10) {
//            message = "The leader has died in battle due to low morale";
//            isAlive = false;
//            DrawText(message.c_str(), x, y, 20, YELLOW);

//        }
//    }
// };

// // rectangle is predefined in raylib
// struct Building {
//    string name;
//    Rectangle rect;  // default having ==poxX=== posY=== width === height 
//    Color color;

// };

// // EventLog: keeps a log of recent events (circular buffer of strings)
// struct EventLog {
//    static const int MAX_EVENTS = 5;
//    char messages[MAX_EVENTS][128];  // fixed-size array for event text
//    int count;  // number of events currently in log (<= MAX_EVENTS)

//    EventLog() : count(0) {
//        // initialize messages with empty strings
//        for (int i = 0; i < MAX_EVENTS; ++i) {
//            messages[i][0] = '\0';
//        }
//    }

//    void add(const char* msg) {
//        if (count < MAX_EVENTS) {
//            // There is room in the log
//            strcpy_s(messages[count], sizeof(messages[count]), msg);
//            count++;
//        }
//        else {
//            // Log is full, remove the oldest (index 0) and shift others up
//            for (int i = 1; i < MAX_EVENTS; ++i) {
//                strcpy_s(messages[i - 1], sizeof(messages[i - 1]), messages[i]);
//            }
//            // Put new message at the last slot
//            strcpy_s(messages[MAX_EVENTS - 1], sizeof(messages[MAX_EVENTS - 1]), msg);
//        }
//    }
// };

// // Kingdom: encapsulates the entire state of the simulation and update logic
// class Kingdom {
// public:
//    int day;              // current turn number (e.g., year)
//    SocialClass peasants;
//    SocialClass merchants;
//    SocialClass nobles;
//    Leadership leader;
//    Military army;
//    Economy economy;
//    Resources resources;
//    EventLog events;
//    Population total;

//    // Constructor to initialize the kingdom with default starting values
//    Kingdom() {
//        day = 0;
//        // Initialize social classes
//        peasants.name = "Peasants";
//        peasants.population = 100;   // start with 100 peasants
//        peasants.unrest = 0.0f;
//        merchants.name = "Merchants";
//        merchants.population = 30;   // 30 merchants
//        merchants.unrest = 0.0f;
//        nobles.name = "Nobles";
//        nobles.population = 10;      // 10 nobles
//        nobles.unrest = 0.0f;
//        // Leader
//        leader.title = "King";       // start with a King in power (monarchy)
//        leader.age = 40;             // starting age of the leader
//        // Army
//        army.soldiers = 20;          // small standing army of 20
//        army.training = 50.0f;       // moderately trained
//        army.morale = 80.0f;         // fairly high morale initially
//        army.corruption = 0.0f;      // discipline initially (no corruption yet)
//        // Economy
//        economy.gold = 100.0f;       // initial treasury gold
//        economy.debt = 0.0f;
//        economy.taxRate = 1.0f;      // normal tax rate (100%)
//        economy.inflation = 0.0f;
//        economy.interestRate = 0.05f;
//        economy.corruption = 0.1f;   // some baseline corruption (10%)
//        // Resources
//        resources.food = 200;        // food reserves
//        resources.wood = 100;
//        resources.stone = 50;
//        resources.iron = 30;
//        // Event log is already constructed (empty)

//        total.currentPopulation = peasants.population + merchants.population + nobles.population + army.soldiers;
//    }

//    // Utility: add an event message to the log
//    void addEvent(const char* msg) {
//        events.add(msg);
//    }

//    // The main turn update function which advances the simulation by one cycle
//    void updateday() {
//        day += 1;  // advance turn counter (could represent a year or season)

//        // 1. Resource Production (using peasants for labor)
//        // Determine production from peasants. We'll allocate peasants' labor in fixed proportions:
//        int p = peasants.population;
//        // e.g., 50% farming, 20% woodcutting, 15% quarrying, 15% mining
//        int foodProduced = (int)(p * 0.5f);
//        int woodProduced = (int)(p * 0.2f);
//        int stoneProduced = (int)(p * 0.15f);
//        int ironProduced = (int)(p * 0.15f);
//        // Add a slight random variation to simulate seasons/harvest variability
//        if (p > 0) {
//            // variation ±10%
//            foodProduced += (rand() % (foodProduced / 5 + 1)) - (foodProduced / 10);
//            woodProduced += (rand() % (woodProduced / 5 + 1)) - (woodProduced / 10);
//            stoneProduced += (rand() % (stoneProduced / 5 + 1)) - (stoneProduced / 10);
//            ironProduced += (rand() % (ironProduced / 5 + 1)) - (ironProduced / 10);
//            // ensure not negative
//            if (foodProduced < 0) foodProduced = 0;
//            if (woodProduced < 0) woodProduced = 0;
//            if (stoneProduced < 0) stoneProduced = 0;
//            if (ironProduced < 0) ironProduced = 0;
//        }
//        // Update resources with production
//        resources.food += foodProduced;
//        resources.wood += woodProduced;
//        resources.stone += stoneProduced;
//        resources.iron += ironProduced;

//        // 2. Resource Consumption
//        // Food consumption by population and army
//        int totalPopulation = peasants.population + merchants.population + nobles.population;
//        int foodNeeded = totalPopulation;           // 1 food per person
//        foodNeeded += army.soldiers;                // and 1 food per soldier
//        if (resources.food < foodNeeded) {
//            // Not enough food to feed everyone -> Famine
//            int deficit = foodNeeded - resources.food;
//            // Determine how many die from starvation (deficit units of food means roughly that many people starve)
//            int deaths = deficit;
//            // Distribute deaths among classes (peasants suffer first, then merchants, then nobles)
//            int p_deaths = deaths;
//            if (p_deaths > peasants.population) p_deaths = peasants.population;
//            peasants.population -= p_deaths;
//            deaths -= p_deaths;
//            if (deaths > 0) {
//                int m_deaths = deaths;
//                if (m_deaths > merchants.population) m_deaths = merchants.population;
//                merchants.population -= m_deaths;
//                deaths -= m_deaths;
//            }
//            if (deaths > 0) {
//                int n_deaths = deaths;
//                if (n_deaths > nobles.population) n_deaths = nobles.population;
//                nobles.population -= n_deaths;
//                deaths -= n_deaths;
//            }
//            // All food is consumed
//            resources.food = 0;
//            // Increase unrest due to famine
//            peasants.unrest += 20.0f;
//            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
//            merchants.unrest += 10.0f;
//            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
//            // (Nobles might not unrest as much as they are less affected directly)
//            nobles.unrest += 5.0f;
//            if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
//            // Log famine event
//            addEvent("Famine: Severe food shortage! People are starving.");
//        }
//        else {
//            // Enough food, consume it
//            resources.food -= foodNeeded;
//        }

//        // Wood consumption (for heating/building) by population
//        int woodNeeded = (int)(totalPopulation * 0.1f);  // e.g., 0.1 wood per person
//        if (resources.wood < woodNeeded) {
//            // Wood shortage
//            resources.wood = 0;
//            // If people have no firewood, increase unrest (and could cause some deaths in winter, but we skip deaths for simplicity)
//            peasants.unrest += 5.0f;   // peasants suffer cold the most
//            merchants.unrest += 3.0f;
//            nobles.unrest += 1.0f;
//            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
//            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
//            if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
//            addEvent("Hardship: Wood supplies exhausted. People lack firewood!");
//        }
//        else {
//            resources.wood -= woodNeeded;
//        }

//        // Iron consumption for tool/weapon maintenance
//        if (army.soldiers > 0) {
//            int ironNeeded = (int)(army.soldiers * 0.1f);  // e.g., 0.1 iron per soldier per turn for upkeep
//            if (resources.iron < ironNeeded) {
//                // Not enough iron to maintain all weapons
//                army.morale -= 5.0f;  // soldiers upset about poor equipment
//                if (army.morale < 0.0f) army.morale = 0.0f;
//                resources.iron = 0;
//                addEvent("Shortage: Iron is scarce, army equipment is suffering.");
//            }
//            else {
//                resources.iron -= ironNeeded;
//            }
//        }

//        // 3. Economic Management (Tax collection and treasury update)
//        // Calculate tax income from each class
//        // We assume base annual income per person: peasant = 1, merchant = 3, noble = 0 (nobles might not pay taxes, or even cost money)
//        float baseTax = peasants.population * 1.0f + merchants.population * 3.0f + nobles.population * 0.0f;
//        float grossTaxIncome = baseTax * economy.taxRate;
//        // Account for corruption siphoning off some income
//        float netTaxIncome = grossTaxIncome * (1.0f - economy.corruption);
//        economy.gold += netTaxIncome;
//        // Slight inflation adjustment: if gold too high relative to population & resources, increase inflation
//        float economySize = (float)totalPopulation + resources.food * 0.5f; // simplistic measure of economy size (pop + some resource factor)
//        if (economy.gold > economySize * 5.0f) {
//            economy.inflation += 0.02f; // inflation creeps up if gold far exceeds goods
//            if (economy.inflation > 1.0f) economy.inflation = 1.0f; // cap inflation at 100% for sanity
//        }
//        // Military upkeep payment
//        float salaryCost = army.soldiers * 1.0f;  // 1 gold per soldier
//        if (economy.gold < salaryCost) {
//            // Can't pay full salaries
//            float shortfall = salaryCost - economy.gold;
//            economy.gold = 0.0f;
//            // Morale drop proportional to shortfall
//            float moraleDrop = (shortfall / salaryCost) * 20.0f; // drop up to 20 if no pay at all
//            army.morale -= moraleDrop;
//            if (army.morale < 0.0f) army.morale = 0.0f;
//            // Increase army corruption (soldiers resort to looting)
//            army.corruption += 0.05f;
//            if (army.corruption > 1.0f) army.corruption = 1.0f;
//            addEvent("Financial: Unable to pay all soldiers' wages. Morale falls.");
//        }
//        else {
//            // Pay the army
//            economy.gold -= salaryCost;
//            // Slight morale boost for being paid
//            army.morale += 1.0f;
//            if (army.morale > 100.0f) army.morale = 100.0f;
//        }

//        // 4. Military Training update
//        army.training += 2.0f;  // each turn soldiers improve a bit
//        if (army.training > 100.0f) army.training = 100.0f;
//        // Small natural morale recovery or decay toward 50 if no big events:
//        if (army.morale > 50.0f) {
//            army.morale -= 0.5f; // morale gently falls if above average (peacetime boredom maybe)
//            if (army.morale < 50.0f) army.morale = 50.0f;
//        }
//        else if (army.morale < 50.0f) {
//            army.morale += 0.5f; // morale gently rises if below average (time heals wounds)
//            if (army.morale > 50.0f) army.morale = 50.0f;
//        }

//        // 5. Population natural growth and decline
//        // We'll use simple percentages for births and deaths
//        float birthRate = 0.02f;   // 2% births
//        float deathRate = 0.01f;   // 1% natural deaths (excluding event deaths)
//        // Calculate births and deaths based on current class populations
//        int peasantsBirths = (int)(peasants.population * birthRate);
//        int merchantsBirths = (int)(merchants.population * birthRate);
//        int noblesBirths = (int)(nobles.population * birthRate);
//        int peasantsDeaths = (int)(peasants.population * deathRate);
//        int merchantsDeaths = (int)(merchants.population * deathRate);
//        int noblesDeaths = (int)(nobles.population * deathRate);
//        // Apply births/deaths
//        peasants.population += peasantsBirths - peasantsDeaths;
//        merchants.population += merchantsBirths - merchantsDeaths;
//        nobles.population += noblesBirths - noblesDeaths;
//        if (peasants.population < 0) peasants.population = 0;
//        if (merchants.population < 0) merchants.population = 0;
//        if (nobles.population < 0) nobles.population = 0;
//        totalPopulation = peasants.population + merchants.population + nobles.population;
//        // (We could also enforce a housing limit: if wood and stone too low, limit peasants.population growth, but omitted for simplicity)

//        // Leader ages
//        leader.age += 1;
//        // Check natural death of leader
//        if (leader.age > 60) {
//            // After 60, chance of death increases each year
//            int deathRoll = rand() % 100;
//            if (deathRoll < (leader.age - 60)) {
//                // Leader dies of old age
//                char deathMsg[128];
//                sprintf_s(deathMsg, "%s has died of old age at %d.", leader.title, leader.age);
//                addEvent(deathMsg);
              
//            }
//        }

//        // 6. Event Triggers
//        // Prepare some random values for this turn
//        int rand100 = rand() % 100;
//        int rand100b = rand() % 100;
//        bool eventOccurred = false;

//        // **War Event** (5% chance each turn, higher if army is large relative to pop)
//        int warChance = 5;
//        if (army.soldiers > peasants.population / 2) {
//            // If the army is very large (e.g., militaristic or preparing war), maybe war chance increases
//            warChance += 5;
//        }
//        if (!eventOccurred && rand100 < warChance) {
//            // War breaks out
//            eventOccurred = true;
//            // Determine outcome partially by army strength
//            bool victory = (army.training > 70 && army.morale > 50 && army.soldiers > 10) && (rand() % 100 < 50);
//            // Casualties
//            int initialSoldiers = army.soldiers;
//            int soldierLoss = victory ? (army.soldiers * 10 / 100) : (army.soldiers * 30 / 100); // lose 10% if victory, 30% if not
//            if (soldierLoss < 1 && army.soldiers > 0) soldierLoss = 1; // lose at least 1 if any soldiers exist
//            army.soldiers -= soldierLoss;
//            if (army.soldiers < 0) army.soldiers = 0;
//            // Civilian casualties (if war takes place on homeland or via draft)
//            int peasantLoss = victory ? (peasants.population * 2 / 100) : (peasants.population * 5 / 100);
//            peasants.population -= peasantLoss;
//            if (peasants.population < 0) peasants.population = 0;
//            // Resource consumption
//            int foodUse = 20;  // use some food for the army during war
//            if (resources.food < foodUse) foodUse = resources.food;
//            resources.food -= foodUse;
//            int woodUse = 15;
//            if (resources.wood < woodUse) woodUse = resources.wood;
//            resources.wood -= woodUse;
//            int stoneUse = 10;
//            if (resources.stone < stoneUse) stoneUse = resources.stone;
//            resources.stone -= stoneUse;
//            int ironUse = 10;
//            if (resources.iron < ironUse) ironUse = resources.iron;
//            resources.iron -= ironUse;
//            // Cost in gold
//            float warCost = 50.0f;
//            if (economy.gold < warCost) {
//                // not enough gold, go into debt
//                economy.debt += (warCost - economy.gold);
//                economy.gold = 0.0f;
//            }
//            else {
//                economy.gold -= warCost;
//            }
//            // Morale impact
//            if (victory) {
//                army.morale += 5.0f;
//                if (army.morale > 100.0f) army.morale = 100.0f;
//            }
//            else {
//                army.morale -= 10.0f;
//                if (army.morale < 0.0f) army.morale = 0.0f;
//            }
//            // Inflation bump if war cost high
//            economy.inflation += 0.01f;
//            if (economy.inflation > 1.0f) economy.inflation = 1.0f;
//            // Unrest impact: war can cause some unrest due to loss and taxes
//            peasants.unrest += 5.0f;
//            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
//            merchants.unrest += 3.0f; // trade disrupted
//            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
//            // Log war event
//            char warMsg[128];
//            if (victory) {
//                sprintf_s(warMsg, sizeof(warMsg), "War: Victory! We lost %d of %d soldiers.", soldierLoss, initialSoldiers);
//            }
//            else {
//                sprintf_s(warMsg, sizeof(warMsg), "War: Defeat... We lost %d of %d soldiers.", soldierLoss, initialSoldiers);
//            }

//            addEvent(warMsg);
//        }

//        // **Plague Event** (e.g., 3% chance normally, higher after famine)
//        int plagueChance = 3;
//        // If a famine occurred recently (detected by a specific event message or a variable), increase chance. 
//        // For simplicity, we'll check if last event was famine:
//        if (events.count > 0 && strstr(events.messages[events.count - 1], "Famine") != NULL) {
//            plagueChance += 5;
//        }
//        if (!eventOccurred && rand100b < plagueChance) {
//            eventOccurred = true;
//            // Plague strikes
//            int p_loss = peasants.population * 15 / 100;   // 15% peasants die
//            int m_loss = merchants.population * 10 / 100;  // 10% merchants die
//            int n_loss = nobles.population * 5 / 100;      // 5% nobles die (maybe better protected)
//            peasants.population -= p_loss;
//            merchants.population -= m_loss;
//            nobles.population -= n_loss;
//            if (peasants.population < 0) peasants.population = 0;
//            if (merchants.population < 0) merchants.population = 0;
//            if (nobles.population < 0) nobles.population = 0;
//            // Soldiers also suffer
//            int s_loss = army.soldiers * 10 / 100;
//            army.soldiers -= s_loss;
//            if (army.soldiers < 0) army.soldiers = 0;
//            // Unrest might actually drop among peasants if population pressure eased, but let's just not change unrest (or minor drop)
//            peasants.unrest -= 5.0f;
//            if (peasants.unrest < 0.0f) peasants.unrest = 0.0f;
//            // Log plague event
//            addEvent("Plague: A deadly plague spreads, killing many across all classes.");
//        }

//        // **Peasant Revolt Event** (triggered by very high peasant unrest)
//        if (!eventOccurred && peasants.unrest > 90.0f) {
//            eventOccurred = true;
//            // Peasant revolt erupts
//            int revoltLoss = peasants.population * 10 / 100;  // 10% peasants die in the revolt
//            int nobleLoss = nobles.population * 10 / 100;     // perhaps 10% nobles killed if revolt targets them
//            peasants.population -= revoltLoss;
//            nobles.population -= nobleLoss;
//            if (peasants.population < 0) peasants.population = 0;
//            if (nobles.population < 0) nobles.population = 0;
//            // Perhaps the army intervenes - if army morale is low, they might join the revolt; if high, they suppress it.
//            if (army.morale < 30.0f) {
//                // Army sympathizes or is ineffective - the revolt succeeds in toppling the leadership
//                addEvent("Revolt: Peasants rise up! The king has been overthrown in the uprising.");
//                // Change leader to something representing the new order
//                leader.title = "Rebel Leader";
//                leader.age = 30;
//                // Adjust policies: lower taxes to appease rebels
//                economy.taxRate = 0.8f;
//                // Reset peasant unrest (they got what they wanted, for now)
//                peasants.unrest = 20.0f;
//                // Nobles are furious now (lost power)
//                nobles.unrest = 80.0f;
//            }
//            else {
//                // Army loyal, suppresses revolt
//                addEvent("Revolt: Peasant uprising is crushed by the army.");
//                // Suppression might kill some peasants (we already did revoltLoss) and instill fear (unrest down a bit)
//                peasants.unrest = 50.0f;
//                // Perhaps a slight morale drop for army having to kill civilians
//                army.morale -= 5.0f;
//                if (army.morale < 0.0f) army.morale = 0.0f;
//            }
//        }

//        // **Military Coup Event** (triggered by very low army morale)
//        if (!eventOccurred && army.morale < 5.0f && army.soldiers > 0) {
//            eventOccurred = true;
//            addEvent("Coup: The disloyal army has overthrown the government!");
//            // Change leader to military
//            leader.title = "General";
//            leader.age = 40;
//            // Possibly execute or depose some nobles
//            int nobleLoss = nobles.population * 20 / 100;
//            nobles.population -= nobleLoss;
//            if (nobles.population < 0) nobles.population = 0;
//            nobles.unrest = 60.0f;  // nobles uneasy under military rule
//            peasants.unrest = 40.0f; // peasants somewhat neutral or relieved if old tyrants gone
//            merchants.unrest = 50.0f;
//            // Adjust policies: maybe set tax rate to normal (the general might not change it drastically yet)
//            economy.taxRate = 1.0f;
//            // Army morale resets higher because they are in power now
//            army.morale = 50.0f;
//            // Army corruption might drop as the general cracks down on it
//            army.corruption *= 0.5f;
//        }

//        // **Corruption Audit Event** (trigger if corruption high)
//        if (!eventOccurred && economy.corruption > 0.5f) {
//            // 20% chance to conduct an audit if corruption above 50%
//            if ((rand() % 100) < 20) {
//                addEvent("Audit: Corruption scandal uncovered! Officials punished and funds recovered.");
//                // Recover some stolen funds: say 10% of tax income times corruption level
//                float recovered = (peasants.population * 1.0f + merchants.population * 3.0f) * economy.taxRate * economy.corruption;
//                economy.gold += recovered;
//                // Reduce corruption significantly
//                economy.corruption -= 0.3f;
//                if (economy.corruption < 0.0f) economy.corruption = 0.0f;
//                // Perhaps slight unrest change: merchants and peasants happy corruption addressed, nobles uneasy if they were the corrupt
//                peasants.unrest -= 5.0f; if (peasants.unrest < 0.0f) peasants.unrest = 0.0f;
//                merchants.unrest -= 5.0f; if (merchants.unrest < 0.0f) merchants.unrest = 0.0f;
//                nobles.unrest += 5.0f; if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
//            }
//        }
//        // **Extreme corruption betrayal** (if corruption very high and no audit)
//        if (!eventOccurred && economy.corruption > 0.8f) {
//            // If we haven't audited and corruption is extremely high, maybe an official flees with treasury
//            addEvent("Betrayal: The Royal Treasurer absconds with a large portion of the treasury!");
//            // Lose a chunk of gold
//            economy.gold *= 0.5f;
//            // Increase debt because missing money may have been borrowed
//            economy.debt += 50.0f;
//            // Reset corruption a bit (the culprit is gone, ironically)
//            economy.corruption -= 0.5f;
//            if (economy.corruption < 0.0f) economy.corruption = 0.0f;
//        }

//        // **Bankruptcy Event** (if debt too high)
//        if (economy.debt > 500.0f) {
//            addEvent("Bankruptcy: The kingdom defaults on its loans, causing financial chaos!");
//            // Halve the debt (lenders forgive some, or it's restructured)
//            economy.debt *= 0.5f;
//            // Spike inflation due to loss of credibility
//            economy.inflation += 0.5f;
//            if (economy.inflation > 1.0f) economy.inflation = 1.0f;
//            // Increase unrest because economy is in shambles
//            peasants.unrest += 10.0f; if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
//            merchants.unrest += 15.0f; if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
//            nobles.unrest += 5.0f; if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
//        }

//        // Final safety clamps on values
//        if (economy.gold < 0.0f) {
//            economy.debt += (-economy.gold);
//            economy.gold = 0.0f;
//        }
//        if (economy.corruption > 1.0f) economy.corruption = 1.0f;
//        if (peasants.unrest < 0.0f) peasants.unrest = 0.0f;
//        if (merchants.unrest < 0.0f) merchants.unrest = 0.0f;
//        if (nobles.unrest < 0.0f) nobles.unrest = 0.0f;
//        if (army.morale < 0.0f) army.morale = 0.0f;
//        if (army.morale > 100.0f) army.morale = 100.0f;
//        if (army.training > 100.0f) army.training = 100.0f;
//        if (army.corruption > 1.0f) army.corruption = 1.0f;
//    }
// };





// class RenderSystem {

// private:
//    Building buildings[10];
//    int buildingCount;
//    Rectangle chiefPosition;
//    float gridSize;
//    int screenWidth;
//    int screenHeight;
//    float nextEventTime = 10.0f; // Track time for random events
//    int x = screenWidth - 260; // side window position
//    int y;
//    string message;
//    int  currentLevel = 1;
//    Kingdom kingdom;


//    Population population;
//    Military military;
//    Leadership leadership;

// public:
//    // update cheif movement
//    void UpdateChiefMovement() {
//        if (IsKeyPressed(KEY_RIGHT) && chiefPosition.x + gridSize < screenWidth) chiefPosition.x += gridSize;
//        if (IsKeyPressed(KEY_LEFT) && chiefPosition.x > 0) chiefPosition.x -= gridSize;
//        if (IsKeyPressed(KEY_DOWN) && chiefPosition.y + gridSize < screenHeight) chiefPosition.y += gridSize;
//        if (IsKeyPressed(KEY_UP) && chiefPosition.y > 0) chiefPosition.y -= gridSize;
//    }


//    // building 0 menue display
//    void menueB0(int option) {
//        switch (option) {
//        case 1:
//            military.DisplayMilitary(920, 150);
//            break;
//        case 2:
//            population.DisplayPopulation(920, 175);
//            break;
//        case 3:
//            leadership.DisplayLeadership(920, 200);
//            break;
//        default:
//            break;
//        }
//    }
//    // building b1 menue display
//    void menueB1(int option) {
//        switch (option) {
//        case 1:
//            military.TrainSoldiers(10, 920, 100);
//            break;
//        case 2:
//            military.DisplayMilitary(920, 125);
//            break;
//        case 3:
//            military.Recruit(population.currentPopulation, 920, 40);
//            military.DisplayMilitary(920, 150);
//            break;
//        default:
//            break;
//        }
//    }
//    // building B2 menue display
//    void menueB2(int option) {
//        switch (option) {
//        case 1:
//            leadership.DisplayLeadership(920, 150);
//            break;
//        case 2:
//            leadership.Election();
//            leadership.DisplayLeadership(920, 175);
//            break;
//        case 3:
//            leadership.militaryRaj();
//            leadership.DisplayLeadership(920, 200);
//            break;
//        default:
//            break;
//        }
//    }


//    void DrawGrid() {
//        for (int x = 0; x < screenWidth; x += gridSize)
//            DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
//        for (int y = 0; y < screenHeight; y += gridSize)
//            DrawLine(0, y, screenWidth, y, LIGHTGRAY);
//    }

//    // anything like title on the corner 
//    void Drawdiscription() const
//    {
//        std::string label = "test" + std::to_string(currentLevel);

//        int fontSize = 20;
//        int textW = MeasureText(label.c_str(), fontSize);
//        int textH = fontSize;

//        int padding = 8;
//        int boxX = 10;
//        int boxY = 10;
//        int boxW = textW + padding * 2;
//        int boxH = textH + padding * 2;

//        DrawRectangleRounded({ (float)boxX, (float)boxY,
//                               (float)boxW, (float)boxH }, 0.25f, 8, DARKBROWN);


//        int textX = boxX + padding;
//        int textY = boxY + padding;
//        DrawText(label.c_str(), textX, textY, fontSize, BEIGE);
//    }

//    // DRAW BULIDINGS
//    void DrawBuildings() {
//        int spacing = gridSize * 3;

//        for (int i = 0; i < buildingCount; i++) {
//            DrawRectangleRec({ buildings[i].rect.x + 5, buildings[i].rect.y + 5, gridSize, gridSize }, Fade(BLACK, 0.2f));

//            bool isNear = CheckCollisionRecs(chiefPosition, buildings[i].rect);
//            Color drawColor = isNear ? GOLD : buildings[i].color;

//            if (buildings[i].name == "Castle") {
//                DrawRectangleRec(buildings[i].rect, DARKGRAY);
//                DrawRectangle(buildings[i].rect.x - 10, buildings[i].rect.y - 40, gridSize / 4, gridSize / 3, DARKGRAY);
//                DrawRectangle(buildings[i].rect.x + gridSize - 10, buildings[i].rect.y - 40, gridSize / 4, gridSize / 3, DARKGRAY);
//                DrawRectangle(buildings[i].rect.x + gridSize / 4, buildings[i].rect.y + gridSize - 20, gridSize / 2, 20, BROWN);
//                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
//                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
//            }

//            else if (buildings[i].name == "Barracks") {
//                DrawRectangleRec(buildings[i].rect, RED);
//                DrawRectangle(buildings[i].rect.x + 5, buildings[i].rect.y - 15, gridSize - 20, 15, RED);
//                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y - 30, 10, 15, DARKBROWN);
//                DrawRectangle(buildings[i].rect.x + 5, buildings[i].rect.y + 10, 30, 15, LIGHTGRAY);
//                DrawRectangle(buildings[i].rect.x + gridSize - 40, buildings[i].rect.y + 10, 30, 15, LIGHTGRAY);
//                DrawRectangle(buildings[i].rect.x + (gridSize / 2) - 20, buildings[i].rect.y + gridSize - 20, 40, 20, BROWN);
//            }

//            else if (buildings[i].name == "Market") {
//                DrawRectangleRec(buildings[i].rect, ORANGE);
//                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 20, gridSize - 20, 20, ORANGE);
//                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize - 20, gridSize - 30, 20, YELLOW);
//                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
//                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
//            }

//            else if (buildings[i].name == "Town Hall") {
//                DrawRectangleRec(buildings[i].rect, BLUE);
//                DrawRectangle(buildings[i].rect.x + gridSize / 3, buildings[i].rect.y - 30, gridSize / 3, 30, DARKBLUE);
//                DrawTriangle({ buildings[i].rect.x + gridSize / 3, buildings[i].rect.y - 30 },
//                    { buildings[i].rect.x + gridSize / 3 + gridSize / 6, buildings[i].rect.y - 60 },
//                    { buildings[i].rect.x + gridSize / 3 + gridSize / 3, buildings[i].rect.y - 30 }, DARKBLUE);
//                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
//                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY);
//            }

//            else if (buildings[i].name == "Blacksmith") {
//                DrawRectangleRec(buildings[i].rect, BROWN);
//                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 15, gridSize - 20, 15, DARKBROWN);
//                DrawRectangle(buildings[i].rect.x + gridSize / 3, buildings[i].rect.y + gridSize - 30, gridSize / 3, 15, DARKGRAY);
//                DrawRectangle(buildings[i].rect.x + 20, buildings[i].rect.y - 30, 10, 15, DARKBROWN);
//                DrawRectangle(buildings[i].rect.x + (gridSize / 2) - 20, buildings[i].rect.y + gridSize - 20, 40, 20, BROWN);
//            }

//            else if (buildings[i].name == "Church") {
//                DrawRectangleRec(buildings[i].rect, PURPLE);
//                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 15, gridSize - 20, 15, DARKPURPLE);
//                DrawRectangle(buildings[i].rect.x + gridSize / 2 - 5, buildings[i].rect.y - 40, 10, 20, DARKPURPLE);
//                DrawTriangle({ buildings[i].rect.x + gridSize / 2 - 5, buildings[i].rect.y - 40 },
//                    { buildings[i].rect.x + gridSize / 2 + 5, buildings[i].rect.y - 60 },
//                    { buildings[i].rect.x + gridSize / 2 + 15, buildings[i].rect.y - 40 }, DARKPURPLE);
//                DrawLine(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y - 60, buildings[i].rect.x + gridSize / 2, buildings[i].rect.y - 75, WHITE);
//                DrawLine(buildings[i].rect.x + gridSize / 2 - 10, buildings[i].rect.y - 67, buildings[i].rect.x + gridSize / 2 + 10, buildings[i].rect.y - 67, WHITE);
//            }

//            DrawText(buildings[i].name.c_str(), buildings[i].rect.x + 5, buildings[i].rect.y + 35, 10, WHITE);

//            if (isNear) {
//                DrawText(("Entered: " + buildings[i].name).c_str(), 10, 560, 18, MAROON);
//            }
//        }

//    }



//    static const Color SKIN;
//    static const Color CLOAK;
//    static const Color BELT;

//    // two characters of cheif
//    void DrawChief2()
//    {
//        // === HEAD & CROWN =======================================================
//        float headR = gridSize * 0.18f;
//        float Heady = chiefPosition.y + 25;
//        float Headx = chiefPosition.x + 50;

//        DrawCircle(Headx, Heady, headR, SKIN);

//        float crownX = Headx - 25;
//        float crownY = chiefPosition.y + 5;

//        DrawRectangle(crownX, crownY, 50, 10, GOLD);

//        float spikeW = 10, spikeH = 12;
//        for (int i = 0; i < 3; ++i)
//        {
//            float sx = crownX + spikeW * (2 * i);
//            DrawTriangle({ sx, crownY },
//                { sx + spikeW, crownY },
//                { sx + spikeW * 0.5f, crownY - spikeH },
//                GOLD);
//        }

//        const Color BELT_CLR = GOLD;
//        const Color BOOT_CLR = DARKBROWN;

//        float bodyW = 40, bodyH = 50;
//        float bodyX = crownX + 5, bodyY = crownY + 35;
//        DrawRectangle(bodyX, bodyY, bodyW, bodyH, BLACK);

//        float beltH = bodyH * 0.14f;
//        DrawRectangle(bodyX, bodyY + bodyH * 0.45f, bodyW, beltH, BELT_CLR);

//        float armW = gridSize * 0.12f, armH = gridSize * 0.30f;
//        float armY = bodyY + bodyH * 0.15f;

//        DrawRectangle(bodyX - armW, armY, armW, armH, BLACK);
//        DrawRectangle(bodyX + bodyW, armY, armW, armH, BLACK);

//        float legW = gridSize * 0.12f, legH = gridSize * 0.28f;
//        float legY = bodyY + bodyH;

//        DrawRectangle(bodyX + bodyW * 0.15f, legY, legW, legH, BOOT_CLR);
//        DrawRectangle(bodyX + bodyW * 0.73f, legY, legW, legH, BOOT_CLR);

//        float swordHandleX = bodyX + bodyW + armW * 0.5f;
//        float swordHandleY = armY - gridSize * 0.04f;
//        float handleH = gridSize * 0.10f;
//        float bladeH = gridSize * 0.50f;
//        float bladeW = 4.0f;

//        DrawRectangle(swordHandleX - bladeW * 0.5f,
//            swordHandleY,
//            bladeW,
//            handleH,
//            BROWN);

//        DrawRectangle(swordHandleX - 10,
//            swordHandleY,
//            20,
//            3,
//            GOLD);

//        DrawRectangle(swordHandleX - bladeW * 0.5f,
//            swordHandleY - bladeH,
//            bladeW,
//            bladeH,
//            LIGHTGRAY);

//        DrawCircle(swordHandleX, swordHandleY + handleH, 3, GOLD);
//    }
//    void pixelCheif() {
//        int chiefx = chiefPosition.x;
//        int chiefy = chiefPosition.y;
//        Image chiefimage = LoadImage("king3.PNG");
//        Texture2D chieftex = LoadTextureFromImage(chiefimage); // Convert image to texture
//        UnloadImage(chiefimage);  // We no longer need the image after converting it to a texture
//        DrawTexture(chieftex, chiefx, chiefy, WHITE);

//    }

//    void drawtree() {
//        int treex = 900;
//        int treey = 20;
//        Image tree = LoadImage("tree.PNG");
//        Texture2D treetex = LoadTextureFromImage(tree); // Convert image to texture
//        UnloadImage(tree);  // We no longer need the image after converting it to a texture
//        DrawTexture(treetex, treex, treey, WHITE);
//        DrawTexture(treetex, 600, 10, WHITE);
//        DrawTexture(treetex, 1100, 10, WHITE);
//        DrawTexture(treetex, 600, 500, WHITE);
//        DrawTexture(treetex, 1100, 500, WHITE);


//    }

//    void DrawChief() {


//        float headR = gridSize * 0.18;
//        float Heady = chiefPosition.y + 25;
//        float Headx = chiefPosition.x + 50;

//        DrawCircle(Headx, Heady, headR, SKIN);

//        float crownX = Headx - 25;
//        float crownY = chiefPosition.y + 5;

//        DrawRectangle(crownX, crownY, 50, 10, GOLD);

//        float spikeW = 10;
//        float spikeH = 12;
//        for (int i = 0; i < 3; ++i)
//        {
//            // sx check 
//            float sx = crownX + spikeW * (2 * i);
//            DrawTriangle({ sx,crownY }, { sx + spikeW,crownY }, { sx + spikeW * 0.5f, crownY - spikeH }, GOLD);
//        }


//        float bodyW = 40;
//        float bodyH = 50;
//        float bodyX = crownX + 5;
//        float bodyY = crownY + 35;
//        DrawRectangle(bodyX, bodyY, bodyW, bodyH, RED);

//        float beltH = bodyH * 0.14;
//        DrawRectangle(bodyX, bodyY + bodyH * 0.45, bodyW, beltH, BELT);


//        float armW = gridSize * 0.12;
//        float armH = gridSize * 0.30;
//        float armY = bodyY + bodyH * 0.15;

//        DrawRectangle(bodyX - armW, armY, armW, armH, RED);
//        DrawRectangle(bodyX + bodyW, armY, armW, armH, RED);


//        float legW = gridSize * 0.12;
//        float legH = gridSize * 0.28;
//        float legY = bodyY + bodyH;

//        DrawRectangle(bodyX + bodyW * 0.15, legY, legW, legH, DARKBROWN);
//        DrawRectangle(bodyX + bodyW * 0.73, legY, legW, legH, DARKBROWN);


//        float sceptreX1 = bodyX + bodyW + armW * 0.5;
//        float sceptreY1 = armY - gridSize * 0.10;
//        float sceptreY2 = sceptreY1 + gridSize * 0.65;
//        DrawLineEx({ sceptreX1, sceptreY1 }, { sceptreX1, sceptreY2 }, 4, GOLD);
//        DrawCircle(sceptreX1, sceptreY1, 6, YELLOW);

//    }





//    void background() {
//        for (int y = 0; y < screenHeight; y++) {
//            DrawLine(0, y, screenWidth, y, GRAY);
//        }
//    }


//    RenderSystem() {}

//    // initialization of the builind dimensions / name / color 
//    // Chief starting position
//    // population military leadership initialization
//    void Init() {
//        screenWidth = 1200;
//        screenHeight = 700;
//        gridSize = 100; // size of each block
//        InitWindow(screenWidth, screenHeight, "Stronghold");
//        SetTargetFPS(60);

//        // Chief starting position
//        chiefPosition = { 1000,500 , (float)gridSize, (float)gridSize };

//        buildingCount = 7;
//        const int x = 8;
//        const int y =3;

//        // initialization of the builind dimensions / name / color 
//        buildings[0] = { "Castle",

//            {(float)(x * gridSize), // rect.x
//            (float)(y * gridSize),  //rect.y
//            (float)gridSize,
//            (float)gridSize},
//            DARKGRAY };

//        buildings[1] = { "Barracks", {(float)((x - 1) * gridSize - 70), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, RED };
//        buildings[2] = { "Market", {(float)((x + 1) * gridSize + 70), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, ORANGE };
//        buildings[3] = { "Granary", {(float)((x - 1) * gridSize - 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, RED };
//        buildings[4] = { "Town Hall", {(float)((x + 1) * gridSize + 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, BLUE };
//        buildings[5] = { "Blacksmith", {(float)(x * gridSize), (float)((y - 2) * gridSize + 40), (float)gridSize, (float)gridSize}, BROWN };
//        buildings[6] = { "Church", {(float)(x * gridSize), (float)((y + 2) * gridSize - 40), (float)gridSize, (float)gridSize}, PURPLE };



//        population = Population(500, 70, 100);
//        military = Military(200, 80, 100, 10, 1000, 50);
//        leadership = Leadership(75);

//        std::srand(std::time(nullptr));
//    }

//    // notice board window
//    void DrawSideWindow() {
//        int sideWindowWidth = 600;
//        int sideWindowHeight = screenHeight; //700
//        int sideWindowX = 0;
//        int sideWindowY = 0;

//        DrawRectangle(sideWindowX, sideWindowY, sideWindowWidth, sideWindowHeight, DARKGRAY);

//        DrawText("Notices", sideWindowX + 10, sideWindowY + 10, 20, WHITE);


//    }
//    void pixelbackground() {
//        int sideWindowX = 0;
//        int sideWindowY = 0;

//        int chiefx = 0;
//        int chiefy = 0;
//        Image chiefimage = LoadImage("back.PNG");
//        Texture2D chieftex = LoadTextureFromImage(chiefimage); // Convert image to texture
//        UnloadImage(chiefimage);  // We no longer need the image after converting it to a texture
//        DrawTexture(chieftex, chiefx, chiefy, WHITE);


//    }
//    // call functions and check the collision of building and the cheif
//    void  Run() {

//        int selectedOption = 0;
//        while (!WindowShouldClose()) {

//            if (IsKeyPressed(KEY_SPACE)) {
//                kingdom.updateday();
//            }
//            UpdateChiefMovement();




//            BeginDrawing();
//            ClearBackground(SKYBLUE);
//            background();
//            DrawGrid();
//            pixelbackground();
//            DrawBuildings();
//            //DrawChief2();
//            pixelCheif();
//            Drawdiscription();
//            //DrawSideWindow();
//            drawtree();

//            ClearBackground(RAYWHITE);

//            // Prepare some colors for different texts
//            Color titleColor = GREEN;
//            Color statColor = GOLD;
//            Color warnColor = RED;
//            Color goodColor = DARKGREEN;
//            Color neutralColor = YELLOW;

//            DrawText(TextFormat("DAY:", kingdom.day),1200, 10, 20, titleColor);
//            DrawText(TextFormat("DAY: ", kingdom.leader.title, kingdom.leader.age),
//                200, 10, 20, titleColor);

//            // Display Population of each class
//            DrawText("Population:", 10, 50, 18, titleColor);
//            DrawText(TextFormat("Peasants: %d", kingdom.peasants.population),
//                30, 70, 18, neutralColor);
//            DrawText(TextFormat("Merchants: %d", kingdom.merchants.population),
//                30, 90, 18, neutralColor);
//            DrawText(TextFormat("Nobles: %d", kingdom.nobles.population),
//                30, 110, 18, neutralColor);
//            // Unrest levels (if noteworthy)
//            DrawText(TextFormat("Unrest - Peasants: %.0f%%, Merchants: %.0f%%, Nobles: %.0f%%",
//                kingdom.peasants.unrest, kingdom.merchants.unrest, kingdom.nobles.unrest),
//                30, 130, 16, (kingdom.peasants.unrest > 50 || kingdom.merchants.unrest > 50 || kingdom.nobles.unrest > 50) ? warnColor : statColor);

//            // Display Resources
//            DrawText("Resources:", 10, 170, 18, titleColor);
//            DrawText(TextFormat("Food: %d", kingdom.resources.food), 30, 190, 18,
//                (kingdom.resources.food < (kingdom.peasants.population + kingdom.merchants.population + kingdom.nobles.population)) ? warnColor : neutralColor);
//            DrawText(TextFormat("Wood: %d", kingdom.resources.wood), 150, 190, 18,
//                (kingdom.resources.wood < (int)((kingdom.peasants.population + kingdom.merchants.population + kingdom.nobles.population) * 0.1f)) ? warnColor : neutralColor);
//            DrawText(TextFormat("Stone: %d", kingdom.resources.stone), 270, 190, 18, neutralColor);
//            DrawText(TextFormat("Iron: %d", kingdom.resources.iron), 390, 190, 18,
//                (kingdom.resources.iron < kingdom.army.soldiers * 1) ? warnColor : neutralColor);

//            // Display Economy
//            DrawText("Economy:", 10, 230, 18, titleColor);
//            DrawText(TextFormat("Gold: %.1f", kingdom.economy.gold), 30, 250, 18,
//                (kingdom.economy.gold < 20.0f) ? warnColor : neutralColor);
//            DrawText(TextFormat("Debt: %.1f", kingdom.economy.debt), 150, 250, 18,
//                (kingdom.economy.debt > 0.0f) ? warnColor : neutralColor);
//            DrawText(TextFormat("Tax Rate: %.0f%%", kingdom.economy.taxRate * 100), 30, 270, 18, neutralColor);
//            DrawText(TextFormat("Inflation: %.0f%%", kingdom.economy.inflation * 100), 200, 270, 18,
//                (kingdom.economy.inflation > 0.3f) ? warnColor : neutralColor);
//            DrawText(TextFormat("Corruption: %.0f%%", kingdom.economy.corruption * 100), 370, 270, 18,
//                (kingdom.economy.corruption > 0.5f) ? warnColor : neutralColor);

//            // Display Military
//            DrawText("Military:", 10, 310, 18, titleColor);
//            DrawText(TextFormat("Soldiers: %d", kingdom.army.soldiers), 30, 330, 18,
//                (kingdom.army.soldiers == 0) ? warnColor : neutralColor);
//            DrawText(TextFormat("Training: %.0f%%", kingdom.army.training), 150, 330, 18,
//                (kingdom.army.training < 30.0f) ? warnColor : neutralColor);
//            DrawText(TextFormat("Morale: %.0f%%", kingdom.army.morale), 300, 330, 18,
//                (kingdom.army.morale < 30.0f) ? warnColor : neutralColor);
//            DrawText(TextFormat("Army Corruption: %.0f%%", kingdom.army.corruption * 100),
//                30, 350, 18, (kingdom.army.corruption > 0.3f) ? warnColor : neutralColor);

//            // Display recent Event Log
//            DrawText("Recent Events:", 10, 390, 18, titleColor);
//            int evCount = kingdom.events.count;
//            for (int i = 0; i < evCount; ++i) {
//                // print each event message, the oldest at i=0 to newest at i=evCount-1
//                DrawText(kingdom.events.messages[i], 30, 410 + 20 * i, 16, statColor);
//            }
//            if (evCount == 0) {
//                DrawText("No significant events yet.", 30, 410, 16, statColor);
//            }

//            // Draw instruction
//            DrawText("Press SPACE to advance turn", 10, 560, 16, WHITE);


//            if (CheckCollisionRecs(chiefPosition, buildings[0].rect)) {
//                DrawText(" Menu", screenWidth - 280, 250, 20, GOLD);
//                DrawText("1. Display Military", screenWidth - 280, 275, 20, WHITE);
//                DrawText("2. Display Population", screenWidth - 280, 300, 20, WHITE);
//                DrawText("3. View Leadership", screenWidth - 280, 325, 20, WHITE);

//                if (IsKeyPressed(KEY_A)) {
//                    selectedOption = 1;
//                }
//                if (IsKeyPressed(KEY_B)) {
//                    selectedOption = 2;
//                }
//                if (IsKeyPressed(KEY_C)) {
//                    selectedOption = 3;
//                }

//                menueB0(selectedOption);
//            }

//            if (CheckCollisionRecs(chiefPosition, buildings[1].rect)) {
//                DrawText("Option Menu", screenWidth - 280, 250, 20, GOLD);
//                DrawText("A. Train Military", screenWidth - 280, 275, 20, WHITE);
//                DrawText("B. display military", screenWidth - 280, 300, 20, WHITE);
//                DrawText("C. Recruit military", screenWidth - 280, 325, 20, WHITE);

//                if (IsKeyPressed(KEY_A)) {
//                    selectedOption = 1;
//                }
//                if (IsKeyPressed(KEY_B)) {
//                    selectedOption = 2;
//                }
//                if (IsKeyPressed(KEY_C)) {
//                    selectedOption = 3;
//                }
//                menueB1(selectedOption);
//            }
//            if (CheckCollisionRecs(chiefPosition, buildings[4].rect)) {
//                DrawText("Option Menu", screenWidth - 280, 250, 20, GOLD);
//                DrawText("1. View Leadership", screenWidth - 280, 275, 20, WHITE);
//                DrawText("2. Start Election", screenWidth - 280, 300, 20, WHITE);
//                DrawText("3. Handle Coup", screenWidth - 280, 325, 20, WHITE);

//                if (IsKeyPressed(KEY_A)) {
//                    selectedOption = 1;
//                }
//                if (IsKeyPressed(KEY_B)) {
//                    selectedOption = 2;
//                }
//                if (IsKeyPressed(KEY_C)) {
//                    selectedOption = 3;
//                }

//                menueB2(selectedOption);
//            }


//            EndDrawing();
//        }
//        CloseWindow();
//    }
// };


// const Color RenderSystem::SKIN = { 255, 224, 189, 255 };
// const Color RenderSystem::CLOAK = { 128,  32,  96, 255 };
// const Color RenderSystem::BELT = { 60,  30,   0, 255 };

// int main() {
//    RenderSystem renderer;
//    renderer.Init();
//    renderer.Run();
//    return 0;
// }
