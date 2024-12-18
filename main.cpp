#include "raylib.h"
#include "Tree.h"
#include "Utils.h"
#include <chrono>

using namespace std;
using namespace chrono;

#define MAX_INPUT_CHARS 1

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Binary Search Tree with File Input and Time Measurement");
    SetTargetFPS(60);

    char inputLetter[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    Rectangle textBox = { screenWidth / 2.0f - 100, 180, 225, 50 };
    bool mouseOnText = false;
    bool drawTree = false;

    TreeNode* root = nullptr;
    vector<string> words = ReadWordsFromFile("words.txt");
    for (auto& word : words) {
        root = Insert(root, word);
    }

    int treeCount = 0;
    int fileCount = 0;
    char searchLetter = '\0';

    double treeSearchTime = 0.0;
    double fileSearchTime = 0.0;

    while (!WindowShouldClose()) {
        if (!drawTree) {
            if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
            else mouseOnText = false;

            if (mouseOnText) {
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();

                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                        inputLetter[letterCount] = (char)key;
                        inputLetter[letterCount + 1] = '\0';
                        letterCount++;
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    inputLetter[letterCount] = '\0';
                }

                if (IsKeyPressed(KEY_ENTER) && letterCount > 0) {
                    drawTree = true;
                    searchLetter = inputLetter[0];

                    auto treeStart = high_resolution_clock::now();
                    treeCount = CountAndHighlight(root, searchLetter);
                    auto treeEnd = high_resolution_clock::now();
                    treeSearchTime = duration<double, milli>(treeEnd - treeStart).count();

                    auto fileStart = high_resolution_clock::now();
                    fileCount = CountWordsInFile(words, searchLetter);
                    auto fileEnd = high_resolution_clock::now();
                    fileSearchTime = duration<double, milli>(fileEnd - fileStart).count();
                }
            }
            else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (!drawTree) {
            DrawText("ENTER A LETTER AND PRESS ENTER", screenWidth / 2 - 200, 100, 20, WHITE);
            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(inputLetter, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
        }
        else {
            DrawText(("Letter: " + string(1, searchLetter)).c_str(), 10, 10, 20, WHITE);
            DrawText(("Count in Tree: " + to_string(treeCount)).c_str(), 10, 40, 20, WHITE);
            DrawText(("Count in File: " + to_string(fileCount)).c_str(), 10, 70, 20, WHITE);
            DrawText(("Tree Search Time: " + to_string(treeSearchTime) + " ms").c_str(), 10, 100, 20, GREEN);
            DrawText(("File Search Time: " + to_string(fileSearchTime) + " ms").c_str(), 10, 130, 20, GREEN);

            DrawTree(root, screenWidth / 2, 100, 300, 1);

            DrawText("Press ESC to close", 10, screenHeight - 30, 20, GRAY);
        }

        EndDrawing();
    }

    DeleteTree(root);
    CloseWindow();
    return 0;
}
