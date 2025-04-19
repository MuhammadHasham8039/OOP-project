#include "raylib.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class Resources {
public:
    int food;
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
// this will devide the population into segments like peasents merchants and nobels
struct SocialClass {
    const char* name;    
    int population;     
    float unrest;        

    SocialClass() : name(""), population(0), unrest(0.0f) {}
};


class Population:public Resources {
public:
    int currentPopulation;
    int employmentRate;

    Population() {}
    Population(int initialPopulation, int employmentRate, int wealth)
        : currentPopulation(initialPopulation), employmentRate(employmentRate) {}

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
        string populationData = "Population: " + std::to_string(currentPopulation) +
            "\nFood Supply: " + to_string(food) +
            "\nEmployment Rate: " +to_string(employmentRate);

        DrawText(populationData.c_str(), x, y, 20, WHITE);
    }


};

class Military: public Resources {
public:
    int soldiersCount;
    int morale;
    float training; // percentage of training skills
    int pay;
    int corruption;
    int costToTrain = 10;
    int trainCoins;
    string message; 

    Military() : message("") {}
    Military(int soldiersCount, int morale, int pay, int corruption, int trainCoins,int training)
        :training(training), trainCoins(trainCoins), soldiersCount(soldiersCount), morale(morale), pay(pay), corruption(corruption) {}

    void Recruit(int population, int x, int y) {
    // recruit 10 percent of the population on call
        int newSoldiers = population / 10;
        soldiersCount += newSoldiers;
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
            soldiersCount -= 5;
        }

        if (corruption > 50) {
            morale -= 20;
            std::cout << "Corruption is high, morale is decreasing" << endl;
        }
    }

    void DisplayMilitary(int x, int y) {
        std::string militaryData = "Soldiers: " + to_string(soldiersCount) +
            "\nMorale: " + to_string(morale) + "%" +
            "\nPay: " + to_string(pay) +
            "\nCorruption: " + to_string(corruption) + "%";

        DrawText(militaryData.c_str(), x, y, 20, WHITE);
    }


    void IncreaseCorruption() {
        corruption += 5;  // Corruption increases over time
    }
};

class Leadership {
public:
    string name;
    int approvalRating;
    bool isAlive;
    int age;
    string message; 

    // initialize X and Y with the best cordinates to dsiplay
    int x;
    int y;
    Leadership() : isAlive(true), message("") {}
    Leadership(int approvalRating) : approvalRating(approvalRating), isAlive(true), message("") {}

    void UpdateLeadership(int change) {
        approvalRating += change;
        if (approvalRating < 0) approvalRating = 0;
        if (approvalRating > 100) approvalRating = 100;
        message = "the approval raiting is increased";
        DrawText(message.c_str(), x, y, 20, WHITE);
    }

    void DisplayLeadership(int x, int y) {
        string leadershipData = "Leadership Approval: " + to_string(approvalRating) + "%";
        DrawText(leadershipData.c_str(), x, y, 20, WHITE);


    }
    // when the approval rating drop 

    void Election() {
        if (approvalRating < 30) {
            message = "The leadership is weak. An election will take place!";
            isAlive = false;  
        }
        else {
            message = "the leadership have the majority";
        }
        if (!message.empty()) {
            DrawText(message.c_str(), x, y, 20, YELLOW);
        }
    }
    // when the leader is not alive 
    void militaryRaj() {
        if (!isAlive) {
            message = "military Raj has occurred";
        }
        else {
            message = "No coupe";
        }
            DrawText(message.c_str(), x, y, 20, YELLOW);
        
    }

    void margya() {
        if (isAlive && approvalRating < 10) {
            message = "The leader has died in battle due to low morale";
            isAlive = false;
            DrawText(message.c_str(), x, y, 20, YELLOW);

        }        
    }
};


// rectangle is predefined in raylib
struct Building {
    string name;
    Rectangle rect;  // default having ==poxX=== posY=== width === height 
    Color color;
    
};

struct EventLog {
    static const int MAX_EVENTS = 10;
    char messages[MAX_EVENTS][128];  
    int count = 0;

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
    void display() {
        int yOffset = 20; // Start displaying from the top-left corner
        for (int i = 0; i < count; i++) {
            DrawText(messages[i], 10, yOffset, 20, YELLOW); // Draw each event at different Y coordinates
            yOffset += 25; // Increase the Y offset for the next message
        }
    }
};


class Kingdom {
public:
    SocialClass peasants;
    SocialClass merchants;
    SocialClass nobles;
    Leadership leader;
    Military army;
    Economy economy;
    Resources resources;
    EventLog events;
    string message;
    int x = 100;
    int y = 100;

    Kingdom() {
        // initialization
       
        // diffrent social classes 
        peasants.name = "Peasants";
        peasants.population = 100;   
        peasants.unrest = 0.0f;
        merchants.name = "Merchants";
        merchants.population = 30; 
        merchants.unrest = 0.0f;
        nobles.name = "Nobles";
        nobles.population = 10;    
        nobles.unrest = 0.0f;


        // leader details
        leader.name = "King";     
        leader.age = 40;            
        
        // army initialization
        army.soldiersCount = 20;          
        army.training = 50.0f;     
        army.morale = 80.0f;        
        army.corruption = 0.0f;     

        // economy initialization
        economy.gold = 100.0f;       
        economy.debt = 0.0f;
        economy.taxRate = 1.0f;     
        economy.inflation = 0.0f;
        economy.interestRate = 0.05f;
        economy.corruption = 0.1f;   

        // Resources
        resources.food = 200;       
        resources.wood = 100;
        resources.stone = 50;
        resources.iron = 30;
    }

    void addEvent(const char* msg) {
        events.add(msg);
    }

    void updateKingdom() {

        //resource Production using peasants for labor
        // Determine production from peasants
        int p = peasants.population;
        // allocation of population to production of differefnt resources

        int foodProduced = (int)(p * 0.5f);
        int woodProduced = (int)(p * 0.2f);
        int stoneProduced = (int)(p * 0.15f);
        int ironProduced = (int)(p * 0.15f);

        // Add a slight random variation to simulate seasons/harvest variability
        if (p > 0) {
            // variation ±10%
            foodProduced += (rand() % (foodProduced / 5 + 1)) - (foodProduced / 10);
            woodProduced += (rand() % (woodProduced / 5 + 1)) - (woodProduced / 10);
            stoneProduced += (rand() % (stoneProduced / 5 + 1)) - (stoneProduced / 10);
            ironProduced += (rand() % (ironProduced / 5 + 1)) - (ironProduced / 10);
            // ensure not negative
            if (foodProduced < 0) foodProduced = 0;
            if (woodProduced < 0) woodProduced = 0;
            if (stoneProduced < 0) stoneProduced = 0;
            if (ironProduced < 0) ironProduced = 0;
        }
        // Update resources with production
        resources.food += foodProduced;
        resources.wood += woodProduced;
        resources.stone += stoneProduced;
        resources.iron += ironProduced;

        //  Resource Consumption
        // the consumption and availability of resources effects the unrest and morale of the kingdom
        // food 
        int totalPopulation = peasants.population + merchants.population + nobles.population;
        int foodNeeded = totalPopulation;
        foodNeeded += army.soldiersCount;
        if (resources.food < foodNeeded) {
            int deficit = foodNeeded - resources.food;
            int deaths = deficit;
            addEvent("Famine!!!! Severe food shortage ");


        }
        if (resources.food = 0) {
            peasants.unrest += 20.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            merchants.unrest += 10.0f;
            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            nobles.unrest += 5.0f;
            if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
            addEvent("unrest is increaing");
        }


        // Wood consumption
        int woodNeeded = (int)(totalPopulation * 0.1f);

        // wood shortage
        if (resources.wood < woodNeeded) {
            resources.wood = 0;
            peasants.unrest += 5.0f;
            merchants.unrest += 3.0f;
            nobles.unrest += 1.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
            addEvent("wood supply fallen (ani pe gai)");
        }
        else {
            resources.wood -= woodNeeded;
        }

        if (army.soldiersCount > 0) {
            int ironNeeded = (int)(army.soldiersCount * 0.1f);
            if (resources.iron < ironNeeded) {
                army.morale -= 5.0f;
                if (army.morale < 0.0f) army.morale = 0.0f;
                resources.iron = 0;
                addEvent("loha khatam ab kya karen USTAD!!!");
            }
            else {
                resources.iron -= ironNeeded;
            }
        }

        //  Economic Management 
        // taking fixed rate of tax from different social classes 
        float tax = peasants.population * 1.0f + merchants.population * 3.0f + nobles.population * 0.0f;

        economy.gold += tax;

        float economySize = (float)totalPopulation + resources.food + resources.wood + resources.iron + resources.stone;

        // higher gold than the economy size means that people have the ability to spend more which 
        // incraese spending anf raise prices
        if (economy.gold > economySize * 5.0f) {
            economy.inflation += 0.02f;
        }


        // managing the salaries of the military 

        float salaryCost = army.soldiersCount * 1.0f;
        if (economy.gold < salaryCost) {
            float shortfall = salaryCost - economy.gold;
            // increase the bedt if the salaries cannot be paid
            economy.debt += shortfall;
            economy.gold = 0.0f;
            float moraleDrop = (shortfall / salaryCost) * 20.0f;
            army.morale -= moraleDrop;

            army.corruption += 0.05f;
            addEvent("Paisa khatam hogya USTAD");
        }
        else {
            economy.gold -= salaryCost;
            army.morale += 1.0f;
        }

        //  military

        army.training += 1.0;  // with time the trainign increase slowly


        // population 

        // natural changes 
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

        // exception handling for negative values
        if (peasants.population < 0) {
            peasants.population = 0;
        }
        if (merchants.population < 0) {
            merchants.population = 0;
        }
        if (nobles.population < 0) {
            nobles.population = 0;
        }
        totalPopulation = peasants.population + merchants.population + nobles.population;


        // Leader ages
        leader.age += 1;
        // Check natural death of leader
        if (leader.age > 100) {

            int deathRoll = rand() % 100;

            if (deathRoll < (leader.age - 60)) {

                char deathMsg[128];
                sprintf_s(deathMsg, "Badshah mar gya.", leader.name, leader.age);
                addEvent(deathMsg);
            }
        }
  
    }
};

class RenderSystem {

private:
    Building buildings[10];
    int buildingCount;
    Rectangle chiefPosition;
    float gridSize;
    int screenWidth;
    int screenHeight;
    float nextEventTime = 10.0f; // Track time for random events
    int x = screenWidth - 260; // side window position
    int y;
    string message;
    int  currentLevel = 1;            // <─ start at level 1


    Population population;
    Military military;
    Leadership leadership;

    void UpdateChiefMovement() {
        if (IsKeyPressed(KEY_RIGHT) && chiefPosition.x + gridSize < screenWidth) chiefPosition.x += gridSize;
        if (IsKeyPressed(KEY_LEFT) && chiefPosition.x > 0) chiefPosition.x -= gridSize;
        if (IsKeyPressed(KEY_DOWN) && chiefPosition.y + gridSize < screenHeight) chiefPosition.y += gridSize;
        if (IsKeyPressed(KEY_UP) && chiefPosition.y > 0) chiefPosition.y -= gridSize;
    }



    void menueB0(int option) {
        switch (option) {
        case 1:
            military.DisplayMilitary(920, 150);
            break;
        case 2:
            population.DisplayPopulation(920, 175);
            break;
        case 3:
            leadership.DisplayLeadership(920, 200);
            break;
        default:
            break;
        }
    }
    void menueB1(int option) {
        switch (option) {
        case 1:
            military.TrainSoldiers(10, 920, 100);
            break;
        case 2:
            military.DisplayMilitary(920, 125);
            break;
        case 3:
            military.Recruit(population.currentPopulation, 920, 40);
            military.DisplayMilitary(920, 150);
            break;
        default:
            break;
        }
    }
    void menueB2(int option) {
        switch (option) {
        case 1:
            leadership.DisplayLeadership(920, 150);
            break;
        case 2:
            leadership.Election();
            leadership.DisplayLeadership(920, 175);
            break;
        case 3:
            leadership.militaryRaj();
            leadership.DisplayLeadership(920, 200);
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

    // check and learn
    void DrawLevel() const
    {
        std::string label = "test" + std::to_string(currentLevel);

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
        int spacing = gridSize * 3; // Increase space between buildings

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





    static const Color SKIN;
    static const Color CLOAK;
    static const Color BELT;


    void DrawChief() {
     

        float headR = gridSize * 0.18;  
        float Heady = chiefPosition.y + 25;
        float Headx = chiefPosition.x + 50;

        DrawCircle(Headx, Heady, headR, SKIN);  

        float crownX = Headx-25;
        float crownY = chiefPosition.y+5;
        
        DrawRectangle(crownX, crownY, 50, 10, GOLD);

        float spikeW = 10;
        float spikeH = 12;
        for (int i = 0; i < 3; ++i)
        {
            // sx check 
            float sx = crownX + spikeW * (2* i);
            DrawTriangle(  { sx,crownY },  { sx + spikeW,crownY },  { sx + spikeW * 0.5f, crownY - spikeH }, GOLD);
        }

   
        float bodyW = 40;
        float bodyH = 50;
        float bodyX = crownX+5;
        float bodyY = crownY+35;
        DrawRectangle(bodyX, bodyY, bodyW, bodyH, RED);

        float beltH = bodyH * 0.14;
        DrawRectangle(bodyX, bodyY + bodyH * 0.45, bodyW, beltH, BELT);

  
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





    void background () {
        for (int y = 0; y < screenHeight; y++) {
            DrawLine(0, y, screenWidth, y, GRAY);
        }
    }

    void DisplayStats() {
        DrawText("**STATS**", screenWidth - 280, 380, 20, YELLOW); // Display message below the leadership stats
        population.DisplayPopulation(screenWidth - 280, 400);
        military.DisplayMilitary(screenWidth - 280, 490);
        leadership.DisplayLeadership(screenWidth - 280, 550);
    }

public:
    RenderSystem() {}

    void Init() {
        screenWidth = 1200;
        screenHeight = 700;
        gridSize = 100; // size of each block
        InitWindow(screenWidth, screenHeight, "Stronghold");
        SetTargetFPS(60);

        // Chief starting position
        chiefPosition = { 100,400 , (float)gridSize, (float)gridSize };

        buildingCount = 7;
        const int x = 5;
        const int y = 3;

        // initialization of the builind dimensions / name / color 
        buildings[0] = { "Castle", 

            {(float)(x * gridSize), // rect.x
            (float)(y * gridSize),  //rect.y
            (float)gridSize, 
            (float)gridSize},
            DARKGRAY };

        buildings[1] = { "Barracks", {(float)((x - 1) * gridSize - 70), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, RED };
        buildings[2] = { "Market", {(float)((x + 1) * gridSize + 70), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, ORANGE };
        buildings[3] = { "Granary", {(float)((x - 1) * gridSize - 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, GREEN };
        buildings[4] = { "Town Hall", {(float)((x + 1) * gridSize + 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, BLUE };
        buildings[5] = { "Blacksmith", {(float)(x * gridSize), (float)((y - 2) * gridSize + 40), (float)gridSize, (float)gridSize}, BROWN };
        buildings[6] = { "Church", {(float)(x * gridSize), (float)((y + 2) * gridSize - 40), (float)gridSize, (float)gridSize}, PURPLE };



        population = Population(500, 70, 100);
        military = Military(200, 80, 100, 10, 1000,50);
        leadership = Leadership(75);

        std::srand(std::time(nullptr));
    }
    void DrawSideWindow() {
        int sideWindowWidth = 300;
        int sideWindowHeight = screenHeight; //700
        int sideWindowX = screenWidth - sideWindowWidth;
        int sideWindowY = 0;

        DrawRectangle(sideWindowX, sideWindowY, sideWindowWidth, sideWindowHeight, DARKGRAY);

        DrawText("Notices", sideWindowX + 10, sideWindowY + 10, 20, WHITE);


    }


    void  Run() {
        EventLog eventLog;
        Kingdom kingdom1;

        int selectedOption = 0;
        while (!WindowShouldClose()) {
            UpdateChiefMovement();
         
            kingdom1.updateKingdom();

       

            BeginDrawing();
            ClearBackground(SKYBLUE);
            background();
            DrawGrid();
            DrawBuildings();
            DrawChief();
            DrawLevel();


            DrawSideWindow();
            eventLog.display();

            if (CheckCollisionRecs(chiefPosition, buildings[0].rect)) {
                DrawText(" Menu", screenWidth - 280, 250, 20, GOLD);
                DrawText("1. Display Military", screenWidth - 280, 275, 20, WHITE);
                DrawText("2. Display Population", screenWidth - 280, 300, 20, WHITE);
                DrawText("3. View Leadership", screenWidth - 280, 325, 20, WHITE);

                if (IsKeyPressed(KEY_A)) {
                    selectedOption = 1;
                }
                if (IsKeyPressed(KEY_B)) {
                    selectedOption = 2;
                }
                if (IsKeyPressed(KEY_C)) {
                    selectedOption = 3;
                }

                menueB0(selectedOption);
            }

            if (CheckCollisionRecs(chiefPosition, buildings[1].rect)) {
                DrawText("Option Menu", screenWidth - 280, 250, 20, GOLD);
                DrawText("A. Train Military", screenWidth - 280, 275, 20, WHITE);
                DrawText("B. display military", screenWidth - 280, 300, 20, WHITE);
                DrawText("C. Recruit military", screenWidth - 280, 325, 20, WHITE);

                if (IsKeyPressed(KEY_A)) {
                    selectedOption = 1;
                }
                if (IsKeyPressed(KEY_B)) {
                    selectedOption = 2;
                }
                if (IsKeyPressed(KEY_C)) {
                    selectedOption = 3;
                }
                menueB1(selectedOption);
            }
            if (CheckCollisionRecs(chiefPosition, buildings[4].rect)) {
                DrawText("Option Menu", screenWidth - 280, 250, 20, GOLD);
                DrawText("1. View Leadership", screenWidth - 280, 275, 20, WHITE);
                DrawText("2. Start Election", screenWidth - 280, 300, 20, WHITE);
                DrawText("3. Handle Coup", screenWidth - 280, 325, 20, WHITE);

                if (IsKeyPressed(KEY_A)) {
                    selectedOption = 1;
                }
                if (IsKeyPressed(KEY_B)) {
                    selectedOption = 2;
                }
                if (IsKeyPressed(KEY_C)) {
                    selectedOption = 3;
                }

                menueB2(selectedOption);
            }

            DisplayStats();

            EndDrawing();
        }
        CloseWindow();
    }
};


const Color RenderSystem::SKIN = { 255, 224, 189, 255 };
const Color RenderSystem::CLOAK = { 128,  32,  96, 255 };
const Color RenderSystem::BELT = { 60,  30,   0, 255 };

int main() {
    RenderSystem renderer;
    renderer.Init();
    renderer.Run();
    return 0;
}
