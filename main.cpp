#include "raylib.h"
#include <iostream>

int main() {
    const int screenX = 1200;
    const int screenY = 600;
    int rectYpos = 300;
    int ballVecX = 5;
    int ballVacY = 5;
    int ballposx = 600;
    int ballposy = 300;
    int playerScore = 0;
    int computerScore = 0;
    InitWindow(screenX, screenY, "Pong");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        ballposx = ballposx + ballVecX;
        ballposy = ballposy + ballVacY;

        if(IsKeyDown(KEY_UP)){
            rectYpos = rectYpos - 5;
        } else if (IsKeyDown(KEY_DOWN)){
            rectYpos = rectYpos + 5;
        }


        if(ballposx <= 0) {
            ballVecX = 5;
            computerScore = computerScore + 1;
        } else if (ballposx >= screenX){
            ballVecX = -5;
            playerScore = playerScore + 1;
        } else if (ballposy <= 0){
            ballVacY = 5;
        } else if (ballposy >= screenY){
            ballVacY = -5;
        } else if (ballposx >= 1150 && rectYpos - 40 <= ballposy && ballposy <= rectYpos +40) {
            ballVecX = -5;
        } else if (ballposx <= 55) {
            ballVecX = 5;
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        DrawLine(600,0,600,600, WHITE);
        DrawRectangle(1150, rectYpos - 30, 5, 80, WHITE);
        DrawRectangle(50, ballposy - 30, 5, 80, WHITE);
        DrawCircle(ballposx, ballposy, 5, WHITE);
        DrawText("0", 560, 5, 50, WHITE);
        DrawText("0", 615, 5, 50, WHITE);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}
