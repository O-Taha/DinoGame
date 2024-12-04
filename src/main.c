/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "utility.h" 
#include "player.h"

Game_state game_state = MENU;

int main() {
    // Initialize the game
    SetUpGame();

    // Load sprites
    Texture buns_sprite = LoadTexture("Buns_Spritesheet.png"); //Initializer element is not a compile-time constant : Needs to be initialized during Runtime (i.e. in a function)
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
        DrawScenery(delta);

        switch (game_state) {
			case MENU:
			DrawText("BUNS RUSH", SCREENWIDTH/2, SCREENHEIGHT/4, 50, BLACK);
			if (IsKeyPressed(KEY_SPACE)) game_state = GAME;
			break;

			case GAME:
			
			UpdatePlayerPhysics(&buns, delta);
			UpdatePlayerAnim(&buns);
            UpdatePlayer(&buns);

            UpdateObstacle(&cactus, delta);
			break;

			case GAMEOVER:
			break;
		
		}

        // Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawText("To do:\nFinishing hazards collisions\nSFX\nMusic", 200, 200, 20, BLACK);


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