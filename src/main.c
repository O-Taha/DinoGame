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

<<<<<<< HEAD
    // Load cactus texture
    Texture2D cactusTexture = LoadTexture("cactus.png");
    Obstacle obstacle;
    float scrollSpeed = 400.0f;

    // Initialize the obstacle
    InitializeObstacle(&obstacle, cactusTexture);
=======
Game_state game_state = MENU;

int main ()
{
	SetUpGame();
	Texture buns_sprite = LoadTexture("Buns_Spritesheet.png"); //Initializer element is not a compile-time constant : Needs to be initialized during Runtime (i.e. in a function)

	Rectangle current_frame_sheet = {0.0, 0.0, (float)buns_sprite.width/3.0, (float)buns_sprite.height};
>>>>>>> 5e738a24f89c902c7e9bcfb86ee98711060f97fe

    // Game loop
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

<<<<<<< HEAD
        DrawScenery(delta);
        UpdatePlayerPhysics(&buns, delta);
        UpdatePlayerAnim(&buns);
=======
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float delta = GetFrameTime();	
		DrawScenery(delta);
		switch (game_state) {
			case MENU:
			DrawText("BUNS RUSH", SCREENWIDTH/2, SCREENHEIGHT/4, 50, BLACK);
			if (IsKeyPressed(KEY_SPACE)) game_state = GAME;
			break;

			case GAME:
			
			UpdatePlayerPhysics(&buns, delta);
			UpdatePlayerAnim(&buns);
			break;

			case GAMEOVER:
			break;
		
		}
		
		// drawing
		BeginDrawing();
		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(SKYBLUE);
>>>>>>> 5e738a24f89c902c7e9bcfb86ee98711060f97fe

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
