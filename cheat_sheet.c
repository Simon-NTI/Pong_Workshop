#include "raylib.h"

typedef struct 
{
    // Position
    float position_x;
    float position_y;

    // Velocity
    float velocity_x;
    float velocity_y;

    // Radius
    float radius;
} Ball;

typedef struct
{
    // Position
    float position_x;
    float position_y;
} Padel;

int main()
{
    // Screen dimensions
    int screen_width = 800;
    int screen_height = 600;

    // Padel Dimensions
    int padel_width = 20;
    int padel_height = 100;
    float padel_velocity = 200;

    // Create padels
    Padel padel_1 = {.position_x = 50, .position_y = 300 - padel_height / 2};
    Padel padel_2 = {.position_x = 730, .position_y = 300 - padel_height / 2};

    // Create window
    SetTargetFPS(60);
    InitWindow(screen_width, screen_height, "Pong");

    // Create a ball
    Ball ball = {.position_x = 400, .position_y = 300, .velocity_x = 200, .velocity_y = 150, .radius = 12};

    // Game loop
    while (!WindowShouldClose())
    {
        // ------- Logic -------

        // Update ball position
        ball.position_x += ball.velocity_x * GetFrameTime();
        ball.position_y += ball.velocity_y * GetFrameTime();

        // Collision between ball and walls 
        // Upper wall
        if(ball.position_y - ball.radius < 0)
        {
            ball.velocity_y *= -1;
        }
        // Bottom wall
        if(ball.position_y + ball.radius > screen_height)
        {
            ball.velocity_y *= -1;
        }
        // Left wall
        if(ball.position_x - ball.radius < 0)
        {
            ball.position_x = 400;
            ball.position_y = 300;
        }
        // Right wall
        if(ball.position_x + ball.radius > screen_width)
        {
            ball.position_x = 400;
            ball.position_y = 300;
        }

        // Padel movement
        // Padel 1
        // Take input from players
        if(IsKeyDown(KEY_W))
        {
            padel_1.position_y -= padel_velocity * GetFrameTime();
        }
        if(IsKeyDown(KEY_S))
        {
            padel_1.position_y += padel_velocity * GetFrameTime();
        }
        // Restrict to screen
        if(padel_1.position_y < 0)
        {
            padel_1.position_y = 0;
        }
        if(padel_1.position_y + padel_height > screen_height)
        {
            padel_1.position_y = screen_height - padel_height;
        }

        // Padel 2
        // Take input from players
        if(IsKeyDown(KEY_UP))
        {
            padel_2.position_y -= padel_velocity * GetFrameTime();
        }
        if(IsKeyDown(KEY_DOWN))
        {
            padel_2.position_y += padel_velocity * GetFrameTime();
        }
        // Restrict to screen
        if(padel_2.position_y < 0)
        {
            padel_2.position_y = 0;
        }
        if(padel_2.position_y + padel_height > screen_height)
        {
            padel_2.position_y = screen_height - padel_height;
        }

        // Padel collision
        // Padel 1
        if(CheckCollisionCircleRec(
            (Vector2){.x = ball.position_x, .y = ball.position_y},
            ball.radius,
            (Rectangle){.height = padel_height, .width = padel_width, .x = padel_1.position_x, .y = padel_1.position_y}))
        {
            ball.velocity_x *= -1;
        }
        // Padel 2
        if(CheckCollisionCircleRec(
            (Vector2){.x = ball.position_x, .y = ball.position_y},
            ball.radius,
            (Rectangle){.height = padel_height, .width = padel_width, .x = padel_2.position_x, .y = padel_2.position_y}))
        {
            ball.velocity_x *= -1;
        }

        // ------- Render -------

        BeginDrawing();
        ClearBackground(BLACK);

        // Render ball

        DrawCircle(ball.position_x, ball.position_y, ball.radius, WHITE);
        
        // Render padels

        DrawRectangle(padel_1.position_x, padel_1.position_y, padel_width, padel_height, WHITE);
        DrawRectangle(padel_2.position_x, padel_2.position_y, padel_width, padel_height, WHITE);

        EndDrawing();   
    }
}