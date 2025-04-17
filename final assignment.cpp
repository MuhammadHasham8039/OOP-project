#include "raylib.h"
#include <vector>
#include <string>
#include <cstdio>

// Types of items that can appear on the board
enum ItemType { NONE, COIN, HURDLE, SWORD, SHIELD };

// Structure to hold player state
struct Player {
    int row, col;            // current position on the board
    int gold;                // gold coins collected
    std::vector<std::string> inventory;  // collected helper items (by name)
};

int main() {
    // Window and game initialization
    const int boardSize = 5;
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "2-Player Turn-Based Board Game");
    SetTargetFPS(60);

    // Game board setup: initialize a 5x5 grid with items
    ItemType board[boardSize][boardSize];
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            board[i][j] = NONE;  // start with all cells empty
        }
    }
    // Place coins on the board (increase gold when picked up)
    board[0][4] = COIN;
    board[1][3] = COIN;
    board[2][2] = COIN;
    board[3][1] = COIN;
    board[4][0] = COIN;
    // Place hurdles on the board (require gold to clear)
    board[0][3] = HURDLE;
    board[1][2] = HURDLE;
    board[2][1] = HURDLE;
    board[3][0] = HURDLE;
    // Place helper objects (e.g., Sword and Shield)
    board[1][1] = SWORD;
    board[3][3] = SHIELD;

    // Initialize players
    Player player1 = { 0, 0, 0, {} };       // Player 1 starts at top-left corner
    Player player2 = { boardSize - 1, boardSize - 1, 0, {} };  // Player 2 starts at bottom-right corner
    bool playerOneTurn = true;  // Player 1 starts

    // Visual settings for layout
    const int cellSize = 100;    // size of each grid cell in pixels
    const int xOrigin = 30;     // left margin from window edge for the grid
    const int yOrigin = 50;     // top margin from window edge for the grid
    const int hurdleCost = 5;    // gold cost to buy/clear a hurdle

    // Variables for status messages (e.g., invalid move feedback)
    std::string statusMessage = "";
    int statusMessageFrames = 0;
    const int statusDisplayTime = 120;  // show messages for 120 frames (~2 seconds at 60 FPS)

    // Main game loop
    while (!WindowShouldClose()) {
        // Handle input for the current player's turn
        if (playerOneTurn) {
            // Player 1 controls: Arrow keys
            int newRow = player1.row;
            int newCol = player1.col;
            bool moved = false;

            // Check which arrow key is pressed (one move per turn)
            if (IsKeyPressed(KEY_UP))    newRow--;
            else if (IsKeyPressed(KEY_DOWN))  newRow++;
            else if (IsKeyPressed(KEY_LEFT))  newCol--;
            else if (IsKeyPressed(KEY_RIGHT)) newCol++;

            // If any movement key was pressed (newRow/newCol changed)
            if (newRow != player1.row || newCol != player1.col) {
                // Validate the move
                if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) {
                    // Move is outside the board
                    statusMessage = "Can't move outside the board!";
                    statusMessageFrames = statusDisplayTime;
                }
                else if (newRow == player2.row && newCol == player2.col) {
                    // Move would land on the other player
                    statusMessage = "That space is occupied by Player 2!";
                    statusMessageFrames = statusDisplayTime;
                }
                else if (board[newRow][newCol] == HURDLE) {
                    // Attempting to move onto a hurdle tile
                    if (player1.gold >= hurdleCost) {
                        // Player has enough gold to buy/clear the hurdle
                        player1.gold -= hurdleCost;
                        board[newRow][newCol] = NONE;    // remove the hurdle from the board
                        // Complete the move onto that tile
                        player1.row = newRow;
                        player1.col = newCol;
                        moved = true;
                    }
                    else {
                        // Not enough gold to clear the hurdle – stay put
                        statusMessage = "Not enough gold to pass the hurdle!";
                        statusMessageFrames = statusDisplayTime;
                    }
                }
                else {
                    // Valid move to an empty or item tile
                    player1.row = newRow;
                    player1.col = newCol;
                    moved = true;
                }

                if (moved) {
                    // If the move was successful, pick up any item on the new tile
                    ItemType item = board[player1.row][player1.col];
                    if (item == COIN) {
                        player1.gold += 1;                 // collect coin (increase gold count)
                        board[player1.row][player1.col] = NONE;
                    }
                    else if (item == SWORD) {
                        player1.inventory.push_back("Sword");  // add Sword to inventory
                        board[player1.row][player1.col] = NONE;
                    }
                    else if (item == SHIELD) {
                        player1.inventory.push_back("Shield"); // add Shield to inventory
                        board[player1.row][player1.col] = NONE;
                    }
                    // End Player 1's turn and switch to Player 2
                    playerOneTurn = false;
                    // Clear any status message once a move is made
                    statusMessage.clear();
                    statusMessageFrames = 0;
                }
            }
        }
        else {
            // Player 2 controls: WASD keys
            int newRow = player2.row;
            int newCol = player2.col;
            bool moved = false;

            if (IsKeyPressed(KEY_W)) newRow--;
            else if (IsKeyPressed(KEY_S)) newRow++;
            else if (IsKeyPressed(KEY_A)) newCol--;
            else if (IsKeyPressed(KEY_D)) newCol++;

            if (newRow != player2.row || newCol != player2.col) {
                // Validate Player 2's move
                if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) {
                    statusMessage = "Can't move outside the board!";
                    statusMessageFrames = statusDisplayTime;
                }
                else if (newRow == player1.row && newCol == player1.col) {
                    statusMessage = "That space is occupied by Player 1!";
                    statusMessageFrames = statusDisplayTime;
                }
                else if (board[newRow][newCol] == HURDLE) {
                    if (player2.gold >= hurdleCost) {
                        // Clear the hurdle by paying gold
                        player2.gold -= hurdleCost;
                        board[newRow][newCol] = NONE;
                        player2.row = newRow;
                        player2.col = newCol;
                        moved = true;
                    }
                    else {
                        statusMessage = "Not enough gold to pass the hurdle!";
                        statusMessageFrames = statusDisplayTime;
                    }
                }
                else {
                    player2.row = newRow;
                    player2.col = newCol;
                    moved = true;
                }

                if (moved) {
                    // Pick up item if present
                    ItemType item = board[player2.row][player2.col];
                    if (item == COIN) {
                        player2.gold += 1;
                        board[player2.row][player2.col] = NONE;
                    }
                    else if (item == SWORD) {
                        player2.inventory.push_back("Sword");
                        board[player2.row][player2.col] = NONE;
                    }
                    else if (item == SHIELD) {
                        player2.inventory.push_back("Shield");
                        board[player2.row][player2.col] = NONE;
                    }
                    // Switch to Player 1's turn
                    playerOneTurn = true;
                    statusMessage.clear();
                    statusMessageFrames = 0;
                }
            }
        }

        // Optional: allow quitting the game with the Escape key
        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }

        // Begin drawing the frame
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw current turn indicator at the top
        const char* turnText = playerOneTurn ? "Player 1's Turn" : "Player 2's Turn";
        Color turnColor = playerOneTurn ? RED : BLUE;
        int textWidth = MeasureText(turnText, 24);
        // Center the turn text above the board
        DrawText(turnText, xOrigin + (cellSize * boardSize - textWidth) / 2, 15, 24, turnColor);

        // Draw the 5x5 grid lines
        for (int i = 0; i <= boardSize; ++i) {
            // Horizontal lines
            DrawLine(xOrigin, yOrigin + i * cellSize,
                xOrigin + boardSize * cellSize, yOrigin + i * cellSize, BLACK);
            // Vertical lines
            DrawLine(xOrigin + i * cellSize, yOrigin,
                xOrigin + i * cellSize, yOrigin + boardSize * cellSize, BLACK);
        }

        // Draw items remaining on the board
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board[i][j] == NONE) continue;  // no item to draw
                // Skip drawing an item on a cell currently occupied by a player
                if ((i == player1.row && j == player1.col) || (i == player2.row && j == player2.col)) continue;

                // Calculate cell center position for drawing
                float cellX = xOrigin + j * cellSize;
                float cellY = yOrigin + i * cellSize;
                float centerX = cellX + cellSize / 2.0f;
                float centerY = cellY + cellSize / 2.0f;
                switch (board[i][j]) {
                case COIN:
                    // Draw coin as a gold circle
                    DrawCircle(centerX, centerY, cellSize * 0.2f, GOLD);
                    break;
                case HURDLE:
                    // Draw hurdle as an "X" (two crossed lines)
                    DrawLine(cellX + 10, cellY + 10, cellX + cellSize - 10, cellY + cellSize - 10, MAROON);
                    DrawLine(cellX + cellSize - 10, cellY + 10, cellX + 10, cellY + cellSize - 10, MAROON);
                    break;
                case SWORD:
                    // Draw sword icon as a simple cross (vertical blade + horizontal hilt)
                    DrawLine(centerX, centerY - 10, centerX, centerY + 10, DARKGRAY);
                    DrawLine(centerX - 5, centerY, centerX + 5, centerY, DARKGRAY);
                    break;
                case SHIELD:
                    // Draw shield icon as a filled square (blue)
                    DrawRectangle(centerX - 10, centerY - 10, 20, 20, SKYBLUE);
                    break;
                default:
                    break;
                }
            }
        }

        // Draw Player 1 (red circle with "1")
        float p1CenterX = xOrigin + player1.col * cellSize + cellSize / 2.0f;
        float p1CenterY = yOrigin + player1.row * cellSize + cellSize / 2.0f;
        DrawCircle(p1CenterX, p1CenterY, cellSize * 0.3f, RED);
        DrawText("1", p1CenterX - MeasureText("1", 20) / 2, p1CenterY - 10, 20, WHITE);
        // Draw Player 2 (blue circle with "2")
        float p2CenterX = xOrigin + player2.col * cellSize + cellSize / 2.0f;
        float p2CenterY = yOrigin + player2.row * cellSize + cellSize / 2.0f;
        DrawCircle(p2CenterX, p2CenterY, cellSize * 0.3f, BLUE);
        DrawText("2", p2CenterX - MeasureText("2", 20) / 2, p2CenterY - 10, 20, WHITE);

        // Draw information panels for Player 1 and Player 2 on the right side
        // Draw a vertical separator line and a horizontal line to split player panels
        DrawLine(xOrigin + boardSize * cellSize + 1, 0, xOrigin + boardSize * cellSize + 1, screenHeight, BLACK);
        DrawLine(xOrigin + boardSize * cellSize, screenHeight / 2, screenWidth, screenHeight / 2, BLACK);

        int panelX = xOrigin + boardSize * cellSize + 10;  // starting X position for text in panels
        // Player 1 panel (top half)
        DrawText("Player 1", panelX, 60, 20, RED);
        char goldText[32];
        snprintf(goldText, sizeof(goldText), "Gold: %d", player1.gold);  // Safe snprintf usage
        DrawText(goldText, panelX, 90, 18, BLACK);
        // Prepare inventory string for Player 1
        std::string inv1 = "Items: ";
        if (player1.inventory.empty()) {
            inv1 += "None";
        }
        else {
            for (size_t k = 0; k < player1.inventory.size(); ++k) {
                inv1 += player1.inventory[k];
                if (k < player1.inventory.size() - 1) inv1 += ", ";
            }
        }
        DrawText(inv1.c_str(), panelX, 110, 18, BLACK);

        // Player 2 panel (bottom half)
        DrawText("Player 2", panelX, 360, 20, BLUE);
        snprintf(goldText, sizeof(goldText), "Gold: %d", player2.gold);  // Safe snprintf usage
        DrawText(goldText, panelX, 390, 18, BLACK);
        std::string inv2 = "Items: ";
        if (player2.inventory.empty()) {
            inv2 += "None";
        }
        else {
            for (size_t k = 0; k < player2.inventory.size(); ++k) {
                inv2 += player2.inventory[k];
                if (k < player2.inventory.size() - 1) inv2 += ", ";
            }
        }
        DrawText(inv2.c_str(), panelX, 410, 18, BLACK);

        // Display any status message (e.g., invalid move warning) at the bottom center
        if (statusMessageFrames > 0 && !statusMessage.empty()) {
            int msgWidth = MeasureText(statusMessage.c_str(), 18);
            DrawText(statusMessage.c_str(), (screenWidth - msgWidth) / 2, screenHeight - 30, 18, MAROON);
            statusMessageFrames--;  // decrement timer
        }

        EndDrawing();
    }

    // De-initialize the window and exit
    CloseWindow();
    return 0;
}
