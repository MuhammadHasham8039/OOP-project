#include "raylib.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

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
            message = "Training soldiers... Morale increased!";
        }
        else {
            message = "Not enough resources to train soldiers!";
        }
        if (!message.empty()) {
            DrawText(message.c_str(), x, y, 20, YELLOW);
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
        DrawText(leadershipData.c_str(), x, y, 20, WHITE);

        // Display any messages related to leadership events (election or coup)
        if (!message.empty()) {
            DrawText(message.c_str(), x, y + 40, 20, YELLOW); // Display message below the leadership stats
        }
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
public:
    RenderSystem() {}

    void Init() {
        screenWidth = 1200;
        screenHeight = 700;
        gridSize = 100; // size of each block
        InitWindow(screenWidth, screenHeight, "Stronghold");
        SetTargetFPS(60);

        // Chief starting position
        chiefPosition = { 0, 0, (float)gridSize, (float)gridSize };

        // Manually initialize buildings
        buildingCount = 7;
        const int x = 5;
        const int y = 3;
        buildings[0] = { "Castle", {(float)(x * gridSize), (float)(y * gridSize), (float)gridSize, (float)gridSize}, DARKGRAY };
        buildings[1] = { "Barracks", {(float)((x - 1) * gridSize), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, RED };
        buildings[2] = { "Market", {(float)((x + 1) * gridSize), (float)((y - 1) * gridSize), (float)gridSize, (float)gridSize}, ORANGE };
        buildings[3] = { "Granary", {(float)((x - 1) * gridSize), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, GREEN };
        buildings[4] = { "Town Hall", {(float)((x + 1) * gridSize), (float)((y + 1) * gridSize), (float)gridSize, (float)gridSize}, BLUE };
        buildings[5] = { "Blacksmith", {(float)(x * gridSize), (float)((y - 2) * gridSize), (float)gridSize, (float)gridSize}, BROWN };
        buildings[6] = { "Church", {(float)(x * gridSize), (float)((y + 2) * gridSize), (float)gridSize, (float)gridSize}, PURPLE };

        // Defaults
        socialStructure.AddCitizen(Citizen("ALi", PEASANT));
        socialStructure.AddCitizen(Citizen("Hassam", NOBLE));
        socialStructure.AddCitizen(Citizen("Ahmad", SOLDIER));

        population = Population(500, 100, 70, 100);
        military = Military(200, 80, 100, 100, 10, 1000);
        leadership = Leadership(75);

        std::srand(std::time(nullptr));
    }

    void Run() {
        int selectedOption = 0;  // Track selected menu option
        while (!WindowShouldClose()) {
            UpdateChiefMovement();
            population.UpdatePopulation();
            military.UpdateMilitary();
            leadership.Election();

            // Random event every 10 seconds
            if (GetTime() > nextEventTime) {
                TriggerRandomEvent();
                nextEventTime = GetTime() + 10;  // Trigger next event in 10 seconds
            }

            BeginDrawing();
            ClearBackground(SKYBLUE);

            DrawGradientBackground();

            DrawGrid();
            DrawBuildings();
            DrawChief();


            if (CheckCollisionRecs(chiefPosition, buildings[0].rect)) {
                DrawText("Option Menu", screenWidth - 200, 20, 20, GOLD);
                DrawText("1. Display Military", screenWidth - 200, 50, 20, WHITE);
                DrawText("2. Display Population", screenWidth - 200, 80, 20, WHITE);
                DrawText("3. View Leadership", screenWidth - 200, 110, 20, WHITE);

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
                DrawText("Option Menu", screenWidth - 200, 20, 20, GOLD);
                DrawText("A. Train Military", screenWidth - 200, 50, 20, WHITE);
                DrawText("B. display military", screenWidth - 200, 110, 20, WHITE);
                DrawText("C. Recruit military", screenWidth - 200, 160, 20, WHITE);

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
                DrawText("Option Menu", screenWidth - 200, 20, 20, GOLD);
                DrawText("1. View Leadership", screenWidth - 200, 50, 20, WHITE);
                DrawText("2. Start Election", screenWidth - 200, 80, 20, WHITE);
                DrawText("3. Handle Coup", screenWidth - 200, 110, 20, WHITE);

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

private:
    Building buildings[10];
    int buildingCount;
    Rectangle chiefPosition;
    float gridSize;
    int screenWidth;
    int screenHeight;
    float nextEventTime = 10.0f; // Track time for random events

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

    void TriggerRandomEvent() {
        int eventType = std::rand() % 3;  // 3 different events

        switch (eventType) {
        case 0:  // Famine
            population.foodSupply -= 20;
            std::cout << "A famine has occurred! Food supply decreases." << std::endl;
            break;
        case 1:  // War
            military.soldiersCount += 50;
            std::cout << "War has broken out! The army is reinforced." << std::endl;
            break;
        case 2:  // Rebellion
            leadership.UpdateLeadership(-10);
            socialStructure.ChangeLoyalty(-20);
            std::cout << "A rebellion has started! Leadership and loyalty decrease." << std::endl;
            break;
        }
    }

    void menueB0(int option) {
        switch (option) {
        case 1:
            military.DisplayMilitary(900, 300);
            break;
        case 2:
            population.DisplayPopulation(900, 300);
            break;
        case 3:
            leadership.DisplayLeadership(900, 300);
            break;
        default:
            break;
        }
    }
    void menueB1(int option) {
        switch (option) {
        case 1:
            military.TrainSoldiers(10, 900, 300);
            break;
        case 2:
            military.DisplayMilitary(900, 300);
            break;
        case 3:
            military.Recruit(population.currentPopulation, 900, 300);
            military.DisplayMilitary(900, 300);
            break;
        default:
            break;
        }
    }
    void menueB2(int option) {
        switch (option) {
        case 1:  // View Leadership
            leadership.DisplayLeadership(900, 300);  // Display leadership stats at (900, 300)
            break;
        case 2:  // Start Election
            leadership.Election();  // Trigger election based on approval rating
            leadership.DisplayLeadership(900, 300);  // Display leadership stats after election
            break;
        case 3:  // Handle Coup
            leadership.Coup();  // Trigger coup if leadership is weak
            leadership.DisplayLeadership(900, 300);  // Display leadership stats after coup
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

    void DrawBuildings() {
        for (int i = 0; i < buildingCount; i++) {
            // Shadow effect
            DrawRectangleRec({ buildings[i].rect.x + 5, buildings[i].rect.y + 5, gridSize, gridSize }, Fade(BLACK, 0.2f));

            // Highlight if chief is nearby
            bool isNear = CheckCollisionRecs(chiefPosition, buildings[i].rect);
            Color drawColor = isNear ? GOLD : buildings[i].color;

            DrawRectangleRec(buildings[i].rect, drawColor);
            DrawText(buildings[i].name.c_str(), buildings[i].rect.x + 5, buildings[i].rect.y + 35, 10, WHITE);

            if (isNear) {
                DrawText(("Entered: " + buildings[i].name).c_str(), 10, 560, 18, MAROON);
            }
        }
    }

    void DrawChief() {
        DrawRectangleRounded(chiefPosition, 0.3f, 4, BLACK);
        DrawText("Chief", chiefPosition.x + 10, chiefPosition.y + 35, 10, WHITE);
    }

    void DrawGradientBackground() {
        for (int y = 0; y < screenHeight; y++) {
            Color c = ColorAlpha(BEIGE, (float)y / screenHeight);
            DrawLine(0, y, screenWidth, y, c);
        }
    }

    void DisplayStats() {
        population.DisplayPopulation(10, 10);
        military.DisplayMilitary(10, 100);
        leadership.DisplayLeadership(10, 200);
        socialStructure.PrintLoyalty();
    }
};

int main() {
    RenderSystem renderer;
    renderer.Init();
    renderer.Run();
    return 0;
}

