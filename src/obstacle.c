#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400
#define GROUND_Y 300

typedef enum {
    SMALL_SINGLE,
    SMALL_DOUBLE,
    SMALL_TRIPLE,
    LARGE_SINGLE,
    LARGE_DOUBLE,
    LARGE_TRIPLE,
    CACTUS_TYPE_COUNT
} CactusType;

typedef struct {
    Vector2 position;
    bool active;
    CactusType cactusType;
    Texture2D texture;
    Rectangle hitbox;
} Obstacle;

// Function to initialize a cactus obstacle
void InitializeCactusObstacle(Obstacle* obstacle, Texture2D* cactusTextures) {
    // Randomly select a cactus type
    obstacle->cactusType = GetRandomValue(0, CACTUS_TYPE_COUNT - 1);
    obstacle->texture = cactusTextures[obstacle->cactusType];

    // Position the cactus at the right side of the screen
    obstacle->position = (Vector2){
        WINDOW_WIDTH,
        GROUND_Y - obstacle->texture.height
    };

    obstacle->active = true;

    // Set up initial hitbox (simplified version)
    obstacle->hitbox = (Rectangle){
        obstacle->position.x + 10,  // Small margin
        obstacle->position.y + 5,   // Small margin
        obstacle->texture.width - 20,  // Reduced width
        obstacle->texture.height - 10  // Reduced height
    };
}

int main(void) {
    // Initialize window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cactus Obstacle Test");
    SetTargetFPS(60);

    // Load cactus textures
    Texture2D cactusTextures[CACTUS_TYPE_COUNT];
    cactusTextures[SMALL_SINGLE] = LoadTexture("Assets/Cactus/SmallCactus1.png");
    cactusTextures[SMALL_DOUBLE] = LoadTexture("Assets/Cactus/SmallCactus2.png");
    cactusTextures[SMALL_TRIPLE] = LoadTexture("Assets/Cactus/SmallCactus3.png");
    cactusTextures[LARGE_SINGLE] = LoadTexture("Assets/Cactus/LargeCactus1.png");
    cactusTextures[LARGE_DOUBLE] = LoadTexture("Assets/Cactus/LargeCactus2.png");
    cactusTextures[LARGE_TRIPLE] = LoadTexture("Assets/Cactus/LargeCactus3.png");

    // Initialize obstacle
    Obstacle obstacle = { 0 };
    InitializeCactusObstacle(&obstacle, cactusTextures);

    // Scrolling speed
    float scrollSpeed = 500.0f;

    // Main game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Move obstacle
        if (obstacle.active) {
            obstacle.position.x -= scrollSpeed * deltaTime;

            // Update hitbox position
            obstacle.hitbox.x = obstacle.position.x + 10;
            obstacle.hitbox.y = obstacle.position.y + 5;

            // Reset obstacle when it leaves the screen
            if (obstacle.position.x < -obstacle.texture.width) {
                InitializeCactusObstacle(&obstacle, cactusTextures);
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw ground line
        DrawLine(0, GROUND_Y, WINDOW_WIDTH, GROUND_Y, BLACK);

        // Draw obstacle
        if (obstacle.active) {
            DrawTexture(obstacle.texture, obstacle.position.x, obstacle.position.y, WHITE);

            // Draw hitbox (red rectangle for visualization)
            DrawRectangleLines(
                obstacle.hitbox.x,
                obstacle.hitbox.y,
                obstacle.hitbox.width,
                obstacle.hitbox.height,
                RED
            );
        }

        // Display current cactus type
        DrawText(TextFormat("Cactus Type: %d", obstacle.cactusType), 10, 10, 20, BLACK);

        EndDrawing();
    }

    // Unload textures
    for (int i = 0; i < CACTUS_TYPE_COUNT; i++) {
        UnloadTexture(cactusTextures[i]);
    }

    CloseWindow();
    return 0;
}