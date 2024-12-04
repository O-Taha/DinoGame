#include "raylib.h"
#include "utility.h" 
#include "player.h"

int main() {
    // Initialize the game
    SetUpGame();

    // Load sprites
    Texture buns_sprite = LoadTexture("Buns_Spritesheet.png");
    Texture cactus_texture = LoadTexture("Cactus.png");

    // Initialize player
	//Rectangle defining the area displayed from a sprite sheet
    Rectangle current_frame_sheet = {0.0, 0.0, (float)buns_sprite.width / 3.0, (float)buns_sprite.height};
	Rectangle buns_hitbox = {POSX, -buns_sprite.height, current_frame_sheet.width, current_frame_sheet.height};
    Player buns = {0, 0, buns_hitbox, buns_sprite, JUMPING, 0, 6, 0, current_frame_sheet};
    
    // Initialize scenery
    InitializeCloud(clouds);
    InitializeObstacle(&cactus, cactus_texture);

    // Game loop
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        // Update game objects
        DrawScenery(delta);
        UpdatePlayerPhysics(&buns, delta);
        UpdatePlayerAnim(&buns);

        // Update obstacle
        UpdateObstacle(&cactus, delta);

        // Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawText("To do: Placing elements at right positions\nMenu\nSpawning hazards\nSFX\nMusic", 200, 200, 20, BLACK);
        UpdatePlayer(&buns);

        // Draw the obstacle
        DrawTexture(cactus.texture, cactus.position.x, cactus.position.y, WHITE);

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(buns_sprite);
    UnloadTexture(cactus_texture);
	for (int i = 0; i < MAXCLOUDS; i++) {
		UnloadTexture(clouds[i].sprite);
	}
    CloseWindow();

    return 0;
}