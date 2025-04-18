

#include "raylib.h"   // Raylib library for graphics and input
#include <cstdio>     // for sprintf (if needed) and printf
#include <cstring>    // for strcpy, etc.
#include <cstdlib>    // for rand(), srand()
#include <ctime>      // for time() to seed random

// Constants for screen layout
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Forward declaration of classes (if needed due to dependencies)
struct SocialClass;
struct Army;
struct Leader;
struct Economy;
struct Resources;
struct EventLog;
class Kingdom;

// SocialClass: represents a social group in the kingdom
struct SocialClass {
    const char* name;    // Name of the class (e.g., "Peasants")
    int population;      // Population count
    float unrest;        // Unrest level (0-100 scale)

    SocialClass() : name(""), population(0), unrest(0.0f) {}
};

// Army: represents the military
struct Army {
    int soldiers;       // number of soldiers
    float training;     // training level (0-100)
    float morale;       // morale level (0-100)
    float corruption;   // corruption level (0 to 1, fraction of resources misused)

    Army() : soldiers(0), training(0.0f), morale(0.0f), corruption(0.0f) {}
};

// Leader: represents the current ruler/leadership
struct Leader {
    const char* title;  // Title or type of leader (e.g., "King", "General", "Council")
    int age;            // Age of the leader (for death chance)
    // (Additional traits or policy modifiers can be added if needed)

    Leader() : title(""), age(0) {}
};

// Economy: financial stats including gold, debt, tax rate, inflation, and corruption
struct Economy {
    float gold;         // Treasury gold amount
    float debt;         // Outstanding debt (if gold < 0, we use this to track loans)
    float taxRate;      // Tax rate (1.0 = normal, 0.5 = low taxes, 1.5 = high taxes, etc.)
    float inflation;    // Inflation rate (as a fraction, e.g., 0.1 = 10%)
    float interestRate; // Interest rate on debt (per turn)
    float corruption;   // Government corruption level (0 to 1, portion of income lost)

    Economy() : gold(0.0f), debt(0.0f), taxRate(1.0f), inflation(0.0f), interestRate(0.05f), corruption(0.0f) {}
};

// Resources: stores quantities of basic resources
struct Resources {
    int food;
    int wood;
    int stone;
    int iron;

    Resources() : food(0), wood(0), stone(0), iron(0) {}
};

// EventLog: keeps a log of recent events (circular buffer of strings)
struct EventLog {
    static const int MAX_EVENTS = 5;
    char messages[MAX_EVENTS][128];  // fixed-size array for event text
    int count;  // number of events currently in log (<= MAX_EVENTS)

    EventLog() : count(0) {
        // initialize messages with empty strings
        for (int i = 0; i < MAX_EVENTS; ++i) {
            messages[i][0] = '\0';
        }
    }

    void add(const char* msg) {
        if (count < MAX_EVENTS) {
            // There is room in the log
            strcpy_s(messages[count], sizeof(messages[count]), msg);
            count++;
        }
        else {
            // Log is full, remove the oldest (index 0) and shift others up
            for (int i = 1; i < MAX_EVENTS; ++i) {
                strcpy_s(messages[i - 1], sizeof(messages[i - 1]), messages[i]);
            }
            // Put new message at the last slot
            strcpy_s(messages[MAX_EVENTS - 1], sizeof(messages[MAX_EVENTS - 1]), msg);
        }
    }
};

// Kingdom: encapsulates the entire state of the simulation and update logic
class Kingdom {
public:
    int turn;              // current turn number (e.g., year)
    SocialClass peasants;
    SocialClass merchants;
    SocialClass nobles;
    Leader leader;
    Army army;
    Economy economy;
    Resources resources;
    EventLog events;

    // Constructor to initialize the kingdom with default starting values
    Kingdom() {
        turn = 0;
        // Initialize social classes
        peasants.name = "Peasants";
        peasants.population = 100;   // start with 100 peasants
        peasants.unrest = 0.0f;
        merchants.name = "Merchants";
        merchants.population = 30;   // 30 merchants
        merchants.unrest = 0.0f;
        nobles.name = "Nobles";
        nobles.population = 10;      // 10 nobles
        nobles.unrest = 0.0f;
        // Leader
        leader.title = "King";       // start with a King in power (monarchy)
        leader.age = 40;             // starting age of the leader
        // Army
        army.soldiers = 20;          // small standing army of 20
        army.training = 50.0f;       // moderately trained
        army.morale = 80.0f;         // fairly high morale initially
        army.corruption = 0.0f;      // discipline initially (no corruption yet)
        // Economy
        economy.gold = 100.0f;       // initial treasury gold
        economy.debt = 0.0f;
        economy.taxRate = 1.0f;      // normal tax rate (100%)
        economy.inflation = 0.0f;
        economy.interestRate = 0.05f;
        economy.corruption = 0.1f;   // some baseline corruption (10%)
        // Resources
        resources.food = 200;        // food reserves
        resources.wood = 100;
        resources.stone = 50;
        resources.iron = 30;
        // Event log is already constructed (empty)
    }

    // Utility: add an event message to the log
    void addEvent(const char* msg) {
        events.add(msg);
    }

    // The main turn update function which advances the simulation by one cycle
    void updateTurn() {
        turn += 1;  // advance turn counter (could represent a year or season)

        // 1. Resource Production (using peasants for labor)
        // Determine production from peasants. We'll allocate peasants' labor in fixed proportions:
        int p = peasants.population;
        // e.g., 50% farming, 20% woodcutting, 15% quarrying, 15% mining
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

        // 2. Resource Consumption
        // Food consumption by population and army
        int totalPopulation = peasants.population + merchants.population + nobles.population;
        int foodNeeded = totalPopulation;           // 1 food per person
        foodNeeded += army.soldiers;                // and 1 food per soldier
        if (resources.food < foodNeeded) {
            // Not enough food to feed everyone -> Famine
            int deficit = foodNeeded - resources.food;
            // Determine how many die from starvation (deficit units of food means roughly that many people starve)
            int deaths = deficit;
            // Distribute deaths among classes (peasants suffer first, then merchants, then nobles)
            int p_deaths = deaths;
            if (p_deaths > peasants.population) p_deaths = peasants.population;
            peasants.population -= p_deaths;
            deaths -= p_deaths;
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
            // All food is consumed
            resources.food = 0;
            // Increase unrest due to famine
            peasants.unrest += 20.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            merchants.unrest += 10.0f;
            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            // (Nobles might not unrest as much as they are less affected directly)
            nobles.unrest += 5.0f;
            if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
            // Log famine event
            addEvent("Famine: Severe food shortage! People are starving.");
        }
        else {
            // Enough food, consume it
            resources.food -= foodNeeded;
        }

        // Wood consumption (for heating/building) by population
        int woodNeeded = (int)(totalPopulation * 0.1f);  // e.g., 0.1 wood per person
        if (resources.wood < woodNeeded) {
            // Wood shortage
            resources.wood = 0;
            // If people have no firewood, increase unrest (and could cause some deaths in winter, but we skip deaths for simplicity)
            peasants.unrest += 5.0f;   // peasants suffer cold the most
            merchants.unrest += 3.0f;
            nobles.unrest += 1.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
            addEvent("Hardship: Wood supplies exhausted. People lack firewood!");
        }
        else {
            resources.wood -= woodNeeded;
        }

        // Iron consumption for tool/weapon maintenance
        if (army.soldiers > 0) {
            int ironNeeded = (int)(army.soldiers * 0.1f);  // e.g., 0.1 iron per soldier per turn for upkeep
            if (resources.iron < ironNeeded) {
                // Not enough iron to maintain all weapons
                army.morale -= 5.0f;  // soldiers upset about poor equipment
                if (army.morale < 0.0f) army.morale = 0.0f;
                resources.iron = 0;
                addEvent("Shortage: Iron is scarce, army equipment is suffering.");
            }
            else {
                resources.iron -= ironNeeded;
            }
        }

        // 3. Economic Management (Tax collection and treasury update)
        // Calculate tax income from each class
        // We assume base annual income per person: peasant = 1, merchant = 3, noble = 0 (nobles might not pay taxes, or even cost money)
        float baseTax = peasants.population * 1.0f + merchants.population * 3.0f + nobles.population * 0.0f;
        float grossTaxIncome = baseTax * economy.taxRate;
        // Account for corruption siphoning off some income
        float netTaxIncome = grossTaxIncome * (1.0f - economy.corruption);
        economy.gold += netTaxIncome;
        // Slight inflation adjustment: if gold too high relative to population & resources, increase inflation
        float economySize = (float)totalPopulation + resources.food * 0.5f; // simplistic measure of economy size (pop + some resource factor)
        if (economy.gold > economySize * 5.0f) {
            economy.inflation += 0.02f; // inflation creeps up if gold far exceeds goods
            if (economy.inflation > 1.0f) economy.inflation = 1.0f; // cap inflation at 100% for sanity
        }
        // Military upkeep payment
        float salaryCost = army.soldiers * 1.0f;  // 1 gold per soldier
        if (economy.gold < salaryCost) {
            // Can't pay full salaries
            float shortfall = salaryCost - economy.gold;
            economy.gold = 0.0f;
            // Morale drop proportional to shortfall
            float moraleDrop = (shortfall / salaryCost) * 20.0f; // drop up to 20 if no pay at all
            army.morale -= moraleDrop;
            if (army.morale < 0.0f) army.morale = 0.0f;
            // Increase army corruption (soldiers resort to looting)
            army.corruption += 0.05f;
            if (army.corruption > 1.0f) army.corruption = 1.0f;
            addEvent("Financial: Unable to pay all soldiers' wages. Morale falls.");
        }
        else {
            // Pay the army
            economy.gold -= salaryCost;
            // Slight morale boost for being paid
            army.morale += 1.0f;
            if (army.morale > 100.0f) army.morale = 100.0f;
        }

        // 4. Military Training update
        army.training += 2.0f;  // each turn soldiers improve a bit
        if (army.training > 100.0f) army.training = 100.0f;
        // Small natural morale recovery or decay toward 50 if no big events:
        if (army.morale > 50.0f) {
            army.morale -= 0.5f; // morale gently falls if above average (peacetime boredom maybe)
            if (army.morale < 50.0f) army.morale = 50.0f;
        }
        else if (army.morale < 50.0f) {
            army.morale += 0.5f; // morale gently rises if below average (time heals wounds)
            if (army.morale > 50.0f) army.morale = 50.0f;
        }

        // 5. Population natural growth and decline
        // We'll use simple percentages for births and deaths
        float birthRate = 0.02f;   // 2% births
        float deathRate = 0.01f;   // 1% natural deaths (excluding event deaths)
        // Calculate births and deaths based on current class populations
        int peasantsBirths = (int)(peasants.population * birthRate);
        int merchantsBirths = (int)(merchants.population * birthRate);
        int noblesBirths = (int)(nobles.population * birthRate);
        int peasantsDeaths = (int)(peasants.population * deathRate);
        int merchantsDeaths = (int)(merchants.population * deathRate);
        int noblesDeaths = (int)(nobles.population * deathRate);
        // Apply births/deaths
        peasants.population += peasantsBirths - peasantsDeaths;
        merchants.population += merchantsBirths - merchantsDeaths;
        nobles.population += noblesBirths - noblesDeaths;
        if (peasants.population < 0) peasants.population = 0;
        if (merchants.population < 0) merchants.population = 0;
        if (nobles.population < 0) nobles.population = 0;
        totalPopulation = peasants.population + merchants.population + nobles.population;
        // (We could also enforce a housing limit: if wood and stone too low, limit peasants.population growth, but omitted for simplicity)

        // Leader ages
        leader.age += 1;
        // Check natural death of leader
        if (leader.age > 60) {
            // After 60, chance of death increases each year
            int deathRoll = rand() % 100;
            if (deathRoll < (leader.age - 60)) {
                // Leader dies of old age
                char deathMsg[128];
                sprintf_s(deathMsg, "%s has died of old age at %d.", leader.title, leader.age);
                addEvent(deathMsg);
                // Succession: If it was a King, assume heir takes over as new King age ~30
                if (strcmp(leader.title, "King") == 0 || strcmp(leader.title, "Queen") == 0) {
                    leader.title = "King"; // remain monarchy (for simplicity gender not tracked)
                    leader.age = 30;
                    addEvent("Succession: The crown passes to the heir.");
                }
                else if (strcmp(leader.title, "General") == 0) {
                    // If a military dictator dies, maybe nobles or someone form a council
                    leader.title = "Council";
                    leader.age = 50;
                    addEvent("Succession: A council of nobles takes over after the general's death.");
                }
                else {
                    // Any other leader type, just replace with a similar age new leader
                    leader.age = 40;
                    addEvent("Succession: A new leader takes office.");
                }
            }
        }

        // 6. Event Triggers
        // Prepare some random values for this turn
        int rand100 = rand() % 100;
        int rand100b = rand() % 100;
        bool eventOccurred = false;

        // **War Event** (5% chance each turn, higher if army is large relative to pop)
        int warChance = 5;
        if (army.soldiers > peasants.population / 2) {
            // If the army is very large (e.g., militaristic or preparing war), maybe war chance increases
            warChance += 5;
        }
        if (!eventOccurred && rand100 < warChance) {
            // War breaks out
            eventOccurred = true;
            // Determine outcome partially by army strength
            bool victory = (army.training > 70 && army.morale > 50 && army.soldiers > 10) && (rand() % 100 < 50);
            // Casualties
            int initialSoldiers = army.soldiers;
            int soldierLoss = victory ? (army.soldiers * 10 / 100) : (army.soldiers * 30 / 100); // lose 10% if victory, 30% if not
            if (soldierLoss < 1 && army.soldiers > 0) soldierLoss = 1; // lose at least 1 if any soldiers exist
            army.soldiers -= soldierLoss;
            if (army.soldiers < 0) army.soldiers = 0;
            // Civilian casualties (if war takes place on homeland or via draft)
            int peasantLoss = victory ? (peasants.population * 2 / 100) : (peasants.population * 5 / 100);
            peasants.population -= peasantLoss;
            if (peasants.population < 0) peasants.population = 0;
            // Resource consumption
            int foodUse = 20;  // use some food for the army during war
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
            // Cost in gold
            float warCost = 50.0f;
            if (economy.gold < warCost) {
                // not enough gold, go into debt
                economy.debt += (warCost - economy.gold);
                economy.gold = 0.0f;
            }
            else {
                economy.gold -= warCost;
            }
            // Morale impact
            if (victory) {
                army.morale += 5.0f;
                if (army.morale > 100.0f) army.morale = 100.0f;
            }
            else {
                army.morale -= 10.0f;
                if (army.morale < 0.0f) army.morale = 0.0f;
            }
            // Inflation bump if war cost high
            economy.inflation += 0.01f;
            if (economy.inflation > 1.0f) economy.inflation = 1.0f;
            // Unrest impact: war can cause some unrest due to loss and taxes
            peasants.unrest += 5.0f;
            if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            merchants.unrest += 3.0f; // trade disrupted
            if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            // Log war event
            char warMsg[128];
            if (victory) {
                sprintf_s(warMsg, sizeof(warMsg), "War: Victory! We lost %d of %d soldiers.", soldierLoss, initialSoldiers);
            }
            else {
                sprintf_s(warMsg, sizeof(warMsg), "War: Defeat... We lost %d of %d soldiers.", soldierLoss, initialSoldiers);
            }

            addEvent(warMsg);
        }

        // **Plague Event** (e.g., 3% chance normally, higher after famine)
        int plagueChance = 3;
        // If a famine occurred recently (detected by a specific event message or a variable), increase chance. 
        // For simplicity, we'll check if last event was famine:
        if (events.count > 0 && strstr(events.messages[events.count - 1], "Famine") != NULL) {
            plagueChance += 5;
        }
        if (!eventOccurred && rand100b < plagueChance) {
            eventOccurred = true;
            // Plague strikes
            int p_loss = peasants.population * 15 / 100;   // 15% peasants die
            int m_loss = merchants.population * 10 / 100;  // 10% merchants die
            int n_loss = nobles.population * 5 / 100;      // 5% nobles die (maybe better protected)
            peasants.population -= p_loss;
            merchants.population -= m_loss;
            nobles.population -= n_loss;
            if (peasants.population < 0) peasants.population = 0;
            if (merchants.population < 0) merchants.population = 0;
            if (nobles.population < 0) nobles.population = 0;
            // Soldiers also suffer
            int s_loss = army.soldiers * 10 / 100;
            army.soldiers -= s_loss;
            if (army.soldiers < 0) army.soldiers = 0;
            // Unrest might actually drop among peasants if population pressure eased, but let's just not change unrest (or minor drop)
            peasants.unrest -= 5.0f;
            if (peasants.unrest < 0.0f) peasants.unrest = 0.0f;
            // Log plague event
            addEvent("Plague: A deadly plague spreads, killing many across all classes.");
        }

        // **Peasant Revolt Event** (triggered by very high peasant unrest)
        if (!eventOccurred && peasants.unrest > 90.0f) {
            eventOccurred = true;
            // Peasant revolt erupts
            int revoltLoss = peasants.population * 10 / 100;  // 10% peasants die in the revolt
            int nobleLoss = nobles.population * 10 / 100;     // perhaps 10% nobles killed if revolt targets them
            peasants.population -= revoltLoss;
            nobles.population -= nobleLoss;
            if (peasants.population < 0) peasants.population = 0;
            if (nobles.population < 0) nobles.population = 0;
            // Perhaps the army intervenes - if army morale is low, they might join the revolt; if high, they suppress it.
            if (army.morale < 30.0f) {
                // Army sympathizes or is ineffective - the revolt succeeds in toppling the leadership
                addEvent("Revolt: Peasants rise up! The king has been overthrown in the uprising.");
                // Change leader to something representing the new order
                leader.title = "Rebel Leader";
                leader.age = 30;
                // Adjust policies: lower taxes to appease rebels
                economy.taxRate = 0.8f;
                // Reset peasant unrest (they got what they wanted, for now)
                peasants.unrest = 20.0f;
                // Nobles are furious now (lost power)
                nobles.unrest = 80.0f;
            }
            else {
                // Army loyal, suppresses revolt
                addEvent("Revolt: Peasant uprising is crushed by the army.");
                // Suppression might kill some peasants (we already did revoltLoss) and instill fear (unrest down a bit)
                peasants.unrest = 50.0f;
                // Perhaps a slight morale drop for army having to kill civilians
                army.morale -= 5.0f;
                if (army.morale < 0.0f) army.morale = 0.0f;
            }
        }

        // **Military Coup Event** (triggered by very low army morale)
        if (!eventOccurred && army.morale < 5.0f && army.soldiers > 0) {
            eventOccurred = true;
            addEvent("Coup: The disloyal army has overthrown the government!");
            // Change leader to military
            leader.title = "General";
            leader.age = 40;
            // Possibly execute or depose some nobles
            int nobleLoss = nobles.population * 20 / 100;
            nobles.population -= nobleLoss;
            if (nobles.population < 0) nobles.population = 0;
            nobles.unrest = 60.0f;  // nobles uneasy under military rule
            peasants.unrest = 40.0f; // peasants somewhat neutral or relieved if old tyrants gone
            merchants.unrest = 50.0f;
            // Adjust policies: maybe set tax rate to normal (the general might not change it drastically yet)
            economy.taxRate = 1.0f;
            // Army morale resets higher because they are in power now
            army.morale = 50.0f;
            // Army corruption might drop as the general cracks down on it
            army.corruption *= 0.5f;
        }

        // **Corruption Audit Event** (trigger if corruption high)
        if (!eventOccurred && economy.corruption > 0.5f) {
            // 20% chance to conduct an audit if corruption above 50%
            if ((rand() % 100) < 20) {
                addEvent("Audit: Corruption scandal uncovered! Officials punished and funds recovered.");
                // Recover some stolen funds: say 10% of tax income times corruption level
                float recovered = (peasants.population * 1.0f + merchants.population * 3.0f) * economy.taxRate * economy.corruption;
                economy.gold += recovered;
                // Reduce corruption significantly
                economy.corruption -= 0.3f;
                if (economy.corruption < 0.0f) economy.corruption = 0.0f;
                // Perhaps slight unrest change: merchants and peasants happy corruption addressed, nobles uneasy if they were the corrupt
                peasants.unrest -= 5.0f; if (peasants.unrest < 0.0f) peasants.unrest = 0.0f;
                merchants.unrest -= 5.0f; if (merchants.unrest < 0.0f) merchants.unrest = 0.0f;
                nobles.unrest += 5.0f; if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
            }
        }
        // **Extreme corruption betrayal** (if corruption very high and no audit)
        if (!eventOccurred && economy.corruption > 0.8f) {
            // If we haven't audited and corruption is extremely high, maybe an official flees with treasury
            addEvent("Betrayal: The Royal Treasurer absconds with a large portion of the treasury!");
            // Lose a chunk of gold
            economy.gold *= 0.5f;
            // Increase debt because missing money may have been borrowed
            economy.debt += 50.0f;
            // Reset corruption a bit (the culprit is gone, ironically)
            economy.corruption -= 0.5f;
            if (economy.corruption < 0.0f) economy.corruption = 0.0f;
        }

        // **Bankruptcy Event** (if debt too high)
        if (economy.debt > 500.0f) {
            addEvent("Bankruptcy: The kingdom defaults on its loans, causing financial chaos!");
            // Halve the debt (lenders forgive some, or it's restructured)
            economy.debt *= 0.5f;
            // Spike inflation due to loss of credibility
            economy.inflation += 0.5f;
            if (economy.inflation > 1.0f) economy.inflation = 1.0f;
            // Increase unrest because economy is in shambles
            peasants.unrest += 10.0f; if (peasants.unrest > 100.0f) peasants.unrest = 100.0f;
            merchants.unrest += 15.0f; if (merchants.unrest > 100.0f) merchants.unrest = 100.0f;
            nobles.unrest += 5.0f; if (nobles.unrest > 100.0f) nobles.unrest = 100.0f;
        }

        // Final safety clamps on values
        if (economy.gold < 0.0f) {
            economy.debt += (-economy.gold);
            economy.gold = 0.0f;
        }
        if (economy.corruption > 1.0f) economy.corruption = 1.0f;
        if (peasants.unrest < 0.0f) peasants.unrest = 0.0f;
        if (merchants.unrest < 0.0f) merchants.unrest = 0.0f;
        if (nobles.unrest < 0.0f) nobles.unrest = 0.0f;
        if (army.morale < 0.0f) army.morale = 0.0f;
        if (army.morale > 100.0f) army.morale = 100.0f;
        if (army.training > 100.0f) army.training = 100.0f;
        if (army.corruption > 1.0f) army.corruption = 1.0f;
    }
};

// main function: initialize, run simulation loop, cleanup
int main() {
    // Initialize random seed
    srand((unsigned)time(NULL));

    // Initialize Raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Medieval Kingdom Simulation");
    SetTargetFPS(60);

    // Create kingdom instance
    Kingdom kingdom;

    // Main loop
    while (!WindowShouldClose()) {
        // Input: press SPACE to advance one turn
        if (IsKeyPressed(KEY_SPACE)) {
            kingdom.updateTurn();
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Prepare some colors for different texts
        Color titleColor = BLACK;
        Color statColor = DARKGRAY;
        Color warnColor = RED;
        Color goodColor = DARKGREEN;
        Color neutralColor = BLACK;

        // Display Turn and Leader info
        DrawText(TextFormat("Turn: %d", kingdom.turn), 10, 10, 20, titleColor);
        DrawText(TextFormat("Leader: %s (Age %d)", kingdom.leader.title, kingdom.leader.age),
            200, 10, 20, titleColor);

        // Display Population of each class
        DrawText("Population:", 10, 50, 18, titleColor);
        DrawText(TextFormat("Peasants: %d", kingdom.peasants.population),
            30, 70, 18, neutralColor);
        DrawText(TextFormat("Merchants: %d", kingdom.merchants.population),
            30, 90, 18, neutralColor);
        DrawText(TextFormat("Nobles: %d", kingdom.nobles.population),
            30, 110, 18, neutralColor);
        // Unrest levels (if noteworthy)
        DrawText(TextFormat("Unrest - Peasants: %.0f%%, Merchants: %.0f%%, Nobles: %.0f%%",
            kingdom.peasants.unrest, kingdom.merchants.unrest, kingdom.nobles.unrest),
            30, 130, 16, (kingdom.peasants.unrest > 50 || kingdom.merchants.unrest > 50 || kingdom.nobles.unrest > 50) ? warnColor : statColor);

        // Display Resources
        DrawText("Resources:", 10, 170, 18, titleColor);
        DrawText(TextFormat("Food: %d", kingdom.resources.food), 30, 190, 18,
            (kingdom.resources.food < (kingdom.peasants.population + kingdom.merchants.population + kingdom.nobles.population)) ? warnColor : neutralColor);
        DrawText(TextFormat("Wood: %d", kingdom.resources.wood), 150, 190, 18,
            (kingdom.resources.wood < (int)((kingdom.peasants.population + kingdom.merchants.population + kingdom.nobles.population) * 0.1f)) ? warnColor : neutralColor);
        DrawText(TextFormat("Stone: %d", kingdom.resources.stone), 270, 190, 18, neutralColor);
        DrawText(TextFormat("Iron: %d", kingdom.resources.iron), 390, 190, 18,
            (kingdom.resources.iron < kingdom.army.soldiers * 1) ? warnColor : neutralColor);

        // Display Economy
        DrawText("Economy:", 10, 230, 18, titleColor);
        DrawText(TextFormat("Gold: %.1f", kingdom.economy.gold), 30, 250, 18,
            (kingdom.economy.gold < 20.0f) ? warnColor : neutralColor);
        DrawText(TextFormat("Debt: %.1f", kingdom.economy.debt), 150, 250, 18,
            (kingdom.economy.debt > 0.0f) ? warnColor : neutralColor);
        DrawText(TextFormat("Tax Rate: %.0f%%", kingdom.economy.taxRate * 100), 30, 270, 18, neutralColor);
        DrawText(TextFormat("Inflation: %.0f%%", kingdom.economy.inflation * 100), 200, 270, 18,
            (kingdom.economy.inflation > 0.3f) ? warnColor : neutralColor);
        DrawText(TextFormat("Corruption: %.0f%%", kingdom.economy.corruption * 100), 370, 270, 18,
            (kingdom.economy.corruption > 0.5f) ? warnColor : neutralColor);

        // Display Military
        DrawText("Military:", 10, 310, 18, titleColor);
        DrawText(TextFormat("Soldiers: %d", kingdom.army.soldiers), 30, 330, 18,
            (kingdom.army.soldiers == 0) ? warnColor : neutralColor);
        DrawText(TextFormat("Training: %.0f%%", kingdom.army.training), 150, 330, 18,
            (kingdom.army.training < 30.0f) ? warnColor : neutralColor);
        DrawText(TextFormat("Morale: %.0f%%", kingdom.army.morale), 300, 330, 18,
            (kingdom.army.morale < 30.0f) ? warnColor : neutralColor);
        DrawText(TextFormat("Army Corruption: %.0f%%", kingdom.army.corruption * 100),
            30, 350, 18, (kingdom.army.corruption > 0.3f) ? warnColor : neutralColor);

        // Display recent Event Log
        DrawText("Recent Events:", 10, 390, 18, titleColor);
        int evCount = kingdom.events.count;
        for (int i = 0; i < evCount; ++i) {
            // print each event message, the oldest at i=0 to newest at i=evCount-1
            DrawText(kingdom.events.messages[i], 30, 410 + 20 * i, 16, statColor);
        }
        if (evCount == 0) {
            DrawText("No significant events yet.", 30, 410, 16, statColor);
        }

        // Draw instruction
        DrawText("Press SPACE to advance turn", 10, 560, 16, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
