#include "raylib.h"

int main() {
    InitWindow(400, 300, "Teste Raylib");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Funcionou!", 130, 140, 20, MAROON);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
