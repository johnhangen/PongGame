#include "raylib.h"
#include <iostream>

// structs
typedef struct Ball{
    Vector2 pos;
    Vector2 vel;
} Ball;

typedef struct Brick{
    Vector2 pos;
    bool active;
} Brick;

static void UpdateGame(void);
static void initGame(void);
static void drawGame(void );


const int screenX = 600;
const int screenY = 400;
const int rows = 8;
const int cols = 30;

static Ball ball;
static Brick brick[30][8];

int barX = 280;

int main() {

    initGame();

    while (!WindowShouldClose()){

        UpdateGame();

        // draw
        BeginDrawing();

        drawGame();

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}

void initGame(){
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


    InitWindow(screenX, screenY, "Brick Breaker");
    SetTargetFPS(60);
}

void drawGame(){
    ClearBackground(WHITE);
    DrawRectangle(barX, 370, 80, 5, BLACK);
    DrawCircle(ball.pos.x, ball.pos.y, 5, BLACK);
    for(int i = 0; i <= cols - 1; i++){
        for(int j = 0; j <= rows - 1; j++) {
            if(brick[i][j].active) {
                DrawRectangle(brick[i][j].pos.x, brick[i][j].pos.y, 19, 19, RED);
            }
        }
    }
}

void UpdateGame(){
    // update
    for(int i = 0; i <= cols - 1; i++){
        for(int j = 0; j <= rows - 1; j++) {
            if(ball.pos.y <= brick[i][j].pos.y + 20 &&
               ball.pos.x >= brick[i][j].pos.x &&
               ball.pos.x <= brick[i][j].pos.x + 20 &&
               brick[i][j].active){
                std::cout << "bellow";
                brick[i][j].active = false;
                ball.vel.y = 5;
            }
        }
    }

    ball.pos.x = ball.pos.x + ball.vel.x;
    ball.pos.y = ball.pos.y + ball.vel.y;

    if(IsKeyDown(KEY_LEFT)){
        barX = barX - 10;
    } else if (IsKeyDown(KEY_RIGHT)){
        barX = barX + 10;
    }

    if(ball.pos.x <= 0) {
        ball.vel.x = 5;
    } else if (ball.pos.x >= screenX){
        ball.vel.x = -5;
    } else if (ball.pos.y <= 0){
        ball.vel.y = 5;
    } else if (ball.pos.y >= screenY) {
        ball.pos.x = 300;
        ball.pos.y = 350;
        ball.vel.x = -5;
        ball.vel.y = 5;
        barX = 270;
    } else if (ball.pos.y >= 375 && barX <= ball.pos.x && ball.pos.x <= barX + 80) {
        ball.vel.y = -5;
    }
}