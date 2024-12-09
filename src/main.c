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
    // Initialize the game; among others:
    //Sets "./resources" as working dir for texture loading;
    //Caps at 60 FPS
    //Window size : 1280 x 800
    SetUpGame();

    // Load sprites
    //Initializer element is not a compile-time constant: 
    //Textures need to be initialized during Runtime (i.e. in a function)
    Texture buns_sprite = LoadTexture("Buns_Spritesheet.png"); 

    //Automatic sprite loading system!
    Texture obstacle_sprites[OBSTACLETYPES];
    FilePathList obstacle_paths = LoadDirectoryFiles("./Obstacles"); //Gets all the sprites from "./resources"
    #ifdef DEBUG
    TraceLog(LOG_INFO , "Found %d obstacle paths in directory: %s", obstacle_paths.count, "/resources/Obstacles");
    #endif
    for (int i = 0; i < obstacle_paths.count; i++) {
        #ifdef DEBUG
        TraceLog(LOG_INFO, "File %d: %s", i, GetFileName(obstacle_paths.paths[i]));
        #endif
        obstacle_sprites[i] = LoadTexture(obstacle_paths.paths[i]);
    }

    // Initialize player
	//Rectangle defining the area displayed from a sprite sheet
    Rectangle current_frame_sheet = {0.0, 0.0, (float)buns_sprite.width / 3.0, (float)buns_sprite.height};
	Rectangle buns_hitbox = {POSX, -buns_sprite.height, current_frame_sheet.width, current_frame_sheet.height};
    Player buns = {0, 0, buns_hitbox, buns_sprite, JUMPING, 0, 6, 0, current_frame_sheet};


    // Initialize scenery
    InitializeCloud(clouds);
    InitializeObstacle(&hazard, obstacle_sprites);

    // Game loop
    while (!WindowShouldClose()) {

        float delta = GetFrameTime();

        #ifdef DEBUG // Works because DinoGame.make already contains the -DDEBUG flag (which makes the preprocessor add "#define DEBUG")
        //delta = 0.016; // Use a fixed delta during debugging.
        #endif

        DrawScenery(delta);

        switch (game_state) {
			case MENU:
			DrawText("Buns Rush!", SCREENWIDTH/2, SCREENHEIGHT/4, 50, BLACK);
			if (IsKeyPressed(KEY_SPACE)) game_state = GAME;
			break;

			case GAME:
			
			UpdatePlayerPhysics(&buns, delta);
			UpdatePlayerAnim(&buns);
            UpdatePlayer(&buns);

            UpdateObstacle(&hazard, obstacle_sprites, delta);
			break;

			case GAMEOVER:
			break;
		
		}

        // Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawText("To do:\nFinishing hazards collisions\nSFX\nMusic\nPowerup", 200, 200, 20, BLACK);


        EndDrawing();
    }

    // Cleanup
    UnloadTexture(buns_sprite);
	for (int i = 0; i < MAXCLOUDS; i++) {
		UnloadTexture(clouds[i].sprite);
	}
    for (int i = 0; i < obstacle_paths.count; i++) {
        UnloadTexture(obstacle_sprites[i]);
    }
    UnloadDirectoryFiles(obstacle_paths);
    CloseWindow();

    return 0;
}