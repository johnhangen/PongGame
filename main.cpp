#include "raylib.h"
#include <iostream>

int main() {
    const int screenX = 600;
    const int screenY = 400;
    const int rows = 8;
    const int cols = 30;

    // structs
    typedef struct Ball{
        Vector2 pos;
        Vector2 vel;
    } Ball;

    typedef struct Brick{
        Vector2 pos;
        bool active;
    } Brick;

    static Ball ball;
    static Brick brick[30][8];

    for(int i = 0; i <= cols - 1; i++){
        for(int j = 0; j <= rows - 1; j++) {
            brick[i][j].pos.x = i*20;
            brick[i][j].pos.y = j*20;
            brick[i][j].active = true;
        }
    }

    ball.pos.x = 300;
    ball.pos.y = 350;
    ball.vel.x = -5;
    ball.vel.y = 5;

    int barX = 300;

    InitWindow(screenX, screenY, "Brick Breaker");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        // update
        for(int i = 0; i <= cols - 1; i++){
            for(int j = 0; j <= rows - 1; j++) {
                // hit bellow
                if(ball.pos.y >= brick[i][j].pos.y && ball.pos.x >= brick[i][j].pos.x && brick[i][j].active){
                    std::cout << "bellow";
                    brick[i][j].active = false;
                    ball.vel.x = 5;
                }
            }
        }

        ball.pos.x = ball.pos.x + ball.vel.x;
        ball.pos.y = ball.pos.y + ball.vel.y;

        if(IsKeyDown(KEY_LEFT)){
            barX = barX - 7;
        } else if (IsKeyDown(KEY_RIGHT)){
            barX = barX + 7;
        }

        if(ball.pos.x <= 0) {
            ball.vel.x = 5;
        } else if (ball.pos.x >= screenX){
            ball.vel.x = -5;
        } else if (ball.pos.y <= 0){
            ball.vel.y = 5;
        } else if (ball.pos.y >= screenY) {
            ball.vel.y = -5;
        } else if (ball.pos.y >= 370 && barX - 30 <= ball.pos.x && ball.pos.x <= barX + 30) {
            ball.vel.y = -5;
        }

        // draw
        BeginDrawing();

        ClearBackground(WHITE);
        DrawRectangle(barX, 370, 60, 5, BLACK);
        DrawCircle(ball.pos.x, ball.pos.y, 5, BLACK);
        for(int i = 0; i <= cols - 1; i++){
            for(int j = 0; j <= rows - 1; j++) {
                if(brick[i][j].active) {
                    DrawRectangle(brick[i][j].pos.x, brick[i][j].pos.y, 19, 19, RED);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}