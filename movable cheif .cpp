#include "raylib.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
enum SocialClass {
    PEASANT,
    MERCHANT,
    NOBLE,
    SOLDIER
};

// Citizen structure representing a person in the kingdom
struct Citizen {
    Citizen() {}
    std::string name;
    SocialClass socialClass;
    int health;
    int wealth;
    int loyalty;  // Loyalty to the ruler (0 to 100)

    Citizen(std::string name, SocialClass socialClass)
        : name(name), socialClass(socialClass), health(100), wealth(0), loyalty(100) {}
};

//need to create individual traits and classes for the individuals
class SocialStructure {
public:
    void AddCitizen(const Citizen& citizen) {
        if (citizenCount < maxCitizens) {
            citizens[citizenCount++] = citizen;
        }
    }

    void ChangeLoyalty(int delta) {
        for (int i = 0; i < citizenCount; ++i) {
            citizens[i].loyalty += delta;
            if (citizens[i].loyalty < 0) citizens[i].loyalty = 0;
            if (citizens[i].loyalty > 100) citizens[i].loyalty = 100;
        }
    }

    void PrintLoyalty() {
        for (int i = 0; i < citizenCount; ++i) {
            std::cout << citizens[i].name << " (Class: " << GetClassName(citizens[i].socialClass) << "): Loyalty = " << citizens[i].loyalty << "%" << std::endl;
        }
    }

private:
    static const int maxCitizens = 100;
    Citizen citizens[maxCitizens];
    int citizenCount = 0;

    std::string GetClassName(SocialClass socialClass) {
        switch (socialClass) {
        case PEASANT: return "Peasant";
        case MERCHANT: return "Merchant";
        case NOBLE: return "Noble";
        case SOLDIER: return "Soldier";
        default: return "Unknown";
        }
    }
};

class Population {
public:
    int currentPopulation;
    int foodSupply;
    int employmentRate;
    int wealth;
    Population() {}
    Population(int initialPopulation, int foodSupply, int employmentRate, int wealth)
        : currentPopulation(initialPopulation), foodSupply(foodSupply), employmentRate(employmentRate), wealth(wealth) {}

    void UpdatePopulation() {
        if (foodSupply < 50) {
            currentPopulation -= 5;
        }
        else if (employmentRate > 80) {
            currentPopulation += 10;
        }
    }

    void DisplayPopulation(int x, int y) {
        std::string populationData = "Population: " + std::to_string(currentPopulation) +
            "\nFood Supply: " + std::to_string(foodSupply) +
            "\nEmployment Rate: " + std::to_string(employmentRate) + "%" +
            "\nWealth: " + std::to_string(wealth);

        DrawText(populationData.c_str(), x, y, 20, WHITE);
    }

    void AddWealth(int amount) {
        wealth += amount;
    }
};

// Military system to manage the army
class Military {
public:
    int soldiersCount;
    int morale;
    int pay;
    int foodSupply;
    int corruption;
    int costToTrain = 10;
    int resource;
    std::string message; // Variable to store the message to be displayed

    Military() : message("") {}
    Military(int soldiersCount, int morale, int pay, int foodSupply, int corruption, int resource)
        : resource(resource), soldiersCount(soldiersCount), morale(morale), pay(pay), foodSupply(foodSupply), corruption(corruption) {}

    void Recruit(int population, int x, int y) {
        int newSoldiers = population / 10;
        soldiersCount += newSoldiers;
        message = "Recruited " + std::to_string(newSoldiers) + " soldiers!";
        if (!message.empty()) {
            DrawText(message.c_str(), x, y, 20, YELLOW);
        }
    }

    void TrainSoldiers(int number, int x, int y) {
        if (resource > (number * costToTrain)) {
            morale += 10;
            resource -= (number * costToTrain);
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
        if (foodSupply < 50) {
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
            std::cout << "Corruption is high, morale is decreasing!" << std::endl;
        }
    }

    void DisplayMilitary(int x, int y) {
        std::string militaryData = "Soldiers: " + std::to_string(soldiersCount) +
            "\nMorale: " + std::to_string(morale) + "%" +
            "\nPay: " + std::to_string(pay) +
            "\nCorruption: " + std::to_string(corruption) + "%";

        DrawText(militaryData.c_str(), x, y, 20, WHITE);
    }


    void IncreaseCorruption() {
        corruption += 5;  // Corruption increases over time
    }
};

class Leadership {
public:
    int approvalRating;
    bool isAlive;
    std::string message; // To store the message to display
    int x = 900;
    int y = 300;
    Leadership() : isAlive(true), message("") {}
    Leadership(int approvalRating) : approvalRating(approvalRating), isAlive(true), message("") {}

    void UpdateLeadership(int change) {
        approvalRating += change;
        if (approvalRating < 0) approvalRating = 0;
        if (approvalRating > 100) approvalRating = 100;
    }

    void DisplayLeadership(int x, int y) {
        std::string leadershipData = "Leadership Approval: " + std::to_string(approvalRating) + "%";
        DrawText(leadershipData.c_str(), 920, 580, 20, WHITE);

   
    }

    void Election() {
        if (approvalRating < 30) {
            message = "The leadership is weak. An election will take place!";
            isAlive = false;  // The leader is removed due to the election
        }
        else {
            message = "the leadership have the majority";
        }
        if (!message.empty()) {
            DrawText(message.c_str(), x, y, 20, YELLOW);
        }
    }

    void Coup() {
        if (!isAlive) {
            message = "A coup has occurred! A new leader has taken power.";
        }
        else {
            message = "No coupe";
        }
        if (!message.empty()) {
            DrawText(message.c_str(), x, y, 20, YELLOW);
        }
    }

    void DeathInBattle() {
        if (isAlive && approvalRating < 10) {
            message = "The leader has died in battle due to low morale!";
            isAlive = false;
        }
    }
};



struct Building {
    std::string name;
    Rectangle rect;
    Color color;
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


    SocialStructure socialStructure;
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
            leadership.Coup();  
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
    void DrawLevel() const
    {
        std::string label = "Level " + std::to_string(currentLevel);

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
       

        // --- text centred in the box ------------------------------
        int textX = boxX + padding;
        int textY = boxY + padding;
        DrawText(label.c_str(), textX, textY, fontSize, BEIGE);
    }
    void DrawBuildings() {
        int spacing = gridSize * 3; // Increase space between buildings

        for (int i = 0; i < buildingCount; i++) {
            // Shadow effect
            DrawRectangleRec({ buildings[i].rect.x + 5, buildings[i].rect.y + 5, gridSize, gridSize }, Fade(BLACK, 0.2f));

            // Highlight if chief is nearby
            bool isNear = CheckCollisionRecs(chiefPosition, buildings[i].rect);
            Color drawColor = isNear ? GOLD : buildings[i].color;

            // Castle - Strong Fortress Look
            if (buildings[i].name == "Castle") {
                // Base of the castle (walls)
                DrawRectangleRec(buildings[i].rect, DARKGRAY);
                // Draw turrets
                DrawRectangle(buildings[i].rect.x - 10, buildings[i].rect.y - 40, gridSize / 4, gridSize / 3, DARKGRAY); // Left turret
                DrawRectangle(buildings[i].rect.x + gridSize - 10, buildings[i].rect.y - 40, gridSize / 4, gridSize / 3, DARKGRAY); // Right turret
                // Castle gate
                DrawRectangle(buildings[i].rect.x + gridSize / 4, buildings[i].rect.y + gridSize - 20, gridSize / 2, 20, BROWN);
                // Draw windows
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY); // Window 1
                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY); // Window 2
            }

            // Barracks - Military Style
            else if (buildings[i].name == "Barracks") {
                // Base
                DrawRectangleRec(buildings[i].rect, RED);
                // Roof
                DrawRectangle(buildings[i].rect.x + 5, buildings[i].rect.y - 15, gridSize - 20, 15, RED);
                // Chimney
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y - 30, 10, 15, DARKBROWN);
                // Windows
                DrawRectangle(buildings[i].rect.x + 5, buildings[i].rect.y + 10, 30, 15, LIGHTGRAY); // Left Window
                DrawRectangle(buildings[i].rect.x + gridSize - 40, buildings[i].rect.y + 10, 30, 15, LIGHTGRAY); // Right Window
                // Door
                DrawRectangle(buildings[i].rect.x + (gridSize / 2) - 20, buildings[i].rect.y + gridSize - 20, 40, 20, BROWN);
            }

            // Market - Shop-like with Open Door
            else if (buildings[i].name == "Market") {
                // Base of the market
                DrawRectangleRec(buildings[i].rect, ORANGE);
                // Roof
                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 20, gridSize - 20, 20, ORANGE);
                // Open front door (entrance)
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize - 20, gridSize - 30, 20, YELLOW);
                // Windows
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY); // Window 1
                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY); // Window 2
            }

            // Town Hall - A grand building with a tower
            else if (buildings[i].name == "Town Hall") {
                // Base
                DrawRectangleRec(buildings[i].rect, BLUE);
                // Tower
                DrawRectangle(buildings[i].rect.x + gridSize / 3, buildings[i].rect.y - 30, gridSize / 3, 30, DARKBLUE);
                // Roof of the tower
                DrawTriangle({ buildings[i].rect.x + gridSize / 3, buildings[i].rect.y - 30 },
                    { buildings[i].rect.x + gridSize / 3 + gridSize / 6, buildings[i].rect.y - 60 },
                    { buildings[i].rect.x + gridSize / 3 + gridSize / 3, buildings[i].rect.y - 30 }, DARKBLUE);
                // Windows
                DrawRectangle(buildings[i].rect.x + 15, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY); // Window 1
                DrawRectangle(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y + gridSize / 2, gridSize / 3, 15, LIGHTGRAY); // Window 2
            }

            // Blacksmith - Furnished with a chimney and forge
            else if (buildings[i].name == "Blacksmith") {
                // Base of the blacksmith
                DrawRectangleRec(buildings[i].rect, BROWN);
                // Roof
                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 15, gridSize - 20, 15, DARKBROWN);
                // Furnace
                DrawRectangle(buildings[i].rect.x + gridSize / 3, buildings[i].rect.y + gridSize - 30, gridSize / 3, 15, DARKGRAY);
                // Chimney
                DrawRectangle(buildings[i].rect.x + 20, buildings[i].rect.y - 30, 10, 15, DARKBROWN);
                // Door
                DrawRectangle(buildings[i].rect.x + (gridSize / 2) - 20, buildings[i].rect.y + gridSize - 20, 40, 20, BROWN);
            }

            // Church - Religious and monumental
            else if (buildings[i].name == "Church") {
                // Base of the church
                DrawRectangleRec(buildings[i].rect, PURPLE);
                // Roof
                DrawRectangle(buildings[i].rect.x + 10, buildings[i].rect.y - 15, gridSize - 20, 15, DARKPURPLE);
                // Bell Tower
                DrawRectangle(buildings[i].rect.x + gridSize / 2 - 5, buildings[i].rect.y - 40, 10, 20, DARKPURPLE);
                DrawTriangle({ buildings[i].rect.x + gridSize / 2 - 5, buildings[i].rect.y - 40 },
                    { buildings[i].rect.x + gridSize / 2 + 5, buildings[i].rect.y - 60 },
                    { buildings[i].rect.x + gridSize / 2 + 15, buildings[i].rect.y - 40 }, DARKPURPLE);
                // Cross on top of the church
                DrawLine(buildings[i].rect.x + gridSize / 2, buildings[i].rect.y - 60, buildings[i].rect.x + gridSize / 2, buildings[i].rect.y - 75, WHITE); // Vertical part
                DrawLine(buildings[i].rect.x + gridSize / 2 - 10, buildings[i].rect.y - 67, buildings[i].rect.x + gridSize / 2 + 10, buildings[i].rect.y - 67, WHITE); // Horizontal part
            }

            // Display building name
            DrawText(buildings[i].name.c_str(), buildings[i].rect.x + 5, buildings[i].rect.y + 35, 10, WHITE);

            if (isNear) {
                DrawText(("Entered: " + buildings[i].name).c_str(), 10, 560, 18, MAROON);
            }
        }

    }





    static const Color SKIN;
    static const Color CLOAK;
    static const Color BELT;

 
    void DrawChief()
    {
        float cx = chiefPosition.x;       
        float cy = chiefPosition.y;
        float s = gridSize;                 

    
        float headR = s * 0.18f;           
        Vector2 headCenter = { cx + s * 0.50f, cy + s * 0.28f };
        DrawCircleV(headCenter, headR, SKIN);

       
        float crownH = headR * 0.55f;
        float crownY = headCenter.y - headR - crownH;
        float crownW = headR * 2.0f;
        float crownX = headCenter.x - crownW * 0.5f;
        DrawRectangle(crownX, crownY, crownW, crownH, GOLD);

        float spikeW = crownW / 5.0f;
        float spikeH = crownH * 1.2f;
        for (int i = 0; i < 3; ++i)
        {
            float sx = crownX + spikeW * (1.0f + 1.5f * i);
            DrawTriangle(   { sx,crownY },                    
                { sx + spikeW,     crownY },                  
                { sx + spikeW * 0.5f, crownY - spikeH },     
                GOLD);
        }

        float bodyW = s * 0.40f;
        float bodyH = s * 0.50f;
        float bodyX = cx + (s - bodyW) * 0.5f;
        float bodyY = cy + s * 0.40f;
        DrawRectangle(bodyX, bodyY, bodyW, bodyH, CLOAK);

        float beltH = bodyH * 0.14f;
        DrawRectangle(bodyX, bodyY + bodyH * 0.45f, bodyW, beltH, BELT);

     
        float armW = s * 0.12f;
        float armH = s * 0.25f;
        float armY = bodyY + bodyH * 0.15f;

        DrawRectangle(bodyX - armW, armY, armW, armH, CLOAK);
        DrawRectangle(bodyX + bodyW, armY, armW, armH, CLOAK);

       
        float legW = s * 0.12f;
        float legH = s * 0.28f;
        float legY = bodyY + bodyH;

        DrawRectangle(bodyX + bodyW * 0.15f, legY, legW, legH, DARKBROWN);      
        DrawRectangle(bodyX + bodyW * 0.73f, legY, legW, legH, DARKBROWN);     

       
        float sceptreX1 = bodyX + bodyW + armW * 0.5f;
        float sceptreY1 = armY - s * 0.10f;
        float sceptreY2 = sceptreY1 + s * 0.65f;
        DrawLineEx({ sceptreX1, sceptreY1 }, { sceptreX1, sceptreY2 }, 4, GOLD);
        DrawCircle(sceptreX1, sceptreY1, 6, YELLOW);

  
    }




    void DrawGradientBackground() {
        for (int y = 0; y < screenHeight; y++) {
            Color c = ColorAlpha(BEIGE, (float)y / screenHeight);
            DrawLine(0, y, screenWidth, y, c);
        }
    }

    void DisplayStats() {
        DrawText("**STATS**", screenWidth-280, 380, 20, YELLOW); // Display message below the leadership stats
        population.DisplayPopulation(screenWidth-280,400);
        military.DisplayMilitary(screenWidth - 280, 490);
        leadership.DisplayLeadership(screenWidth-280, 550);
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
        chiefPosition = { 50,350 , (float)gridSize, (float)gridSize };

        buildingCount = 7;
        const int x = 5;
        const int y = 3;
        buildings[0] = { "Castle", {(float)(x * gridSize), (float)(y * gridSize), (float)gridSize, (float)gridSize}, DARKGRAY };
        buildings[1] = { "Barracks", {(float)((x - 1) * gridSize - 70), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, RED };
        buildings[2] = { "Market", {(float)((x + 1) * gridSize + 70), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, ORANGE };
        buildings[3] = { "Granary", {(float)((x - 1) * gridSize - 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, GREEN };
        buildings[4] = { "Town Hall", {(float)((x + 1) * gridSize + 70), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, BLUE };
        buildings[5] = { "Blacksmith", {(float)(x * gridSize), (float)((y - 2) * gridSize + 40), (float)gridSize, (float)gridSize}, BROWN };
        buildings[6] = { "Church", {(float)(x * gridSize), (float)((y + 2) * gridSize - 40), (float)gridSize, (float)gridSize}, PURPLE };

        socialStructure.AddCitizen(Citizen("ALi", PEASANT));
        socialStructure.AddCitizen(Citizen("Hassam", NOBLE));
        socialStructure.AddCitizen(Citizen("Ahmad", SOLDIER));

        population = Population(500, 100, 70, 100);
        military = Military(200, 80, 100, 100, 10, 1000);
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

    // not displyaing the message in the notice box
    void TriggerRandomEvent() {
        int eventType = rand() % 3;
        switch (eventType) {
        case 0:
            population.foodSupply -= 20;
            message = "A famine has occurred!";
            if (!message.empty()) {
                DrawText(message.c_str(), 920, 30, 20, YELLOW);
            }
            break;
        case 1:
            military.soldiersCount += 50;
            message = "War has broken out!";
            if (!message.empty()) {
                DrawText(message.c_str(), 920, 30, 20, YELLOW);
            }
            break;
        case 2:
            leadership.UpdateLeadership(-10);
            socialStructure.ChangeLoyalty(-20);
            message = "A rebellion has started!";
            if (!message.empty()) {
                DrawText(message.c_str(), 300, 300, 20, YELLOW);
            }
            break;
        }
    }

    void  Run() {
        int selectedOption = 0;
        while (!WindowShouldClose()) {
            UpdateChiefMovement();
            population.UpdatePopulation();
            military.UpdateMilitary();
            leadership.Election();

            if (GetTime() > nextEventTime) {
                TriggerRandomEvent();
                nextEventTime = GetTime() + 10;
            }

            BeginDrawing();
            ClearBackground(SKYBLUE);

            DrawGradientBackground();
            DrawGrid();
            DrawBuildings();
            DrawChief();
            DrawLevel();            


            DrawSideWindow();

            if (CheckCollisionRecs(chiefPosition, buildings[0].rect)) {
                DrawText("Option Menu", screenWidth - 280, 250, 20, GOLD);
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

