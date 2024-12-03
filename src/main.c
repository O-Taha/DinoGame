#include "raylib.h"
#include "utility.h" 
#include "player.h"
#include "obstacle.h"

int main() {
    SetUpGame();
    Texture buns_sprite = LoadTexture("Buns_Spritesheet.png");
    Rectangle current_frame_sheet = {0.0, 0.0, (float)buns_sprite.width / 3.0, (float)buns_sprite.height};
    Player buns = {0, 0, buns_sprite, JUMPING, 0, 6, 0, current_frame_sheet};
    InstantiateCloud(clouds);

    // Load cactus texture
    Texture2D cactusTexture = LoadTexture("cactus.png");
    Obstacle obstacle;
    float scrollSpeed = 400.0f;

    // Initialize the obstacle
    InitializeObstacle(&obstacle, cactusTexture);

    // Game loop
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        DrawScenery(delta);
        UpdatePlayerPhysics(&buns, delta);
        UpdatePlayerAnim(&buns);

        // Update obstacle
        UpdateObstacle(&obstacle, delta, scrollSpeed);

        // Check if obstacle is off-screen and reinitialize
        if (IsObstacleOffScreen(&obstacle)) {
            InitializeObstacle(&obstacle, cactusTexture);
        }

        // Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawText("To do: Placing elements at right positions\nMenu\nSpawning hazards\nSFX\nMusic", 200, 200, 20, BLACK);
        UpdatePlayer(&buns);

        // Draw the obstacle
        DrawTexture(obstacle.texture, obstacle.position.x, obstacle.position.y, WHITE);

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(buns_sprite);
    UnloadTexture(cactusTexture);
    CloseWindow();
    return 0;
}
