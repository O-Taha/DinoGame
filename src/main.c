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

// How to run on Linux : run make then the exe is in bin folder -> Press F5 

#include "raylib.h"
#include "../include/resource_dir.h"	// utility header for SearchAndSetResourceDir

//Constants
#define GRAVITY -10

//Player Object
typedef struct {
	float posY;
	Texture sprite;
} Player;

//Functions
	//Utility functions
void SetUpGame() {
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(1280, 800, "Dino Game");
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);
	return;
}

void UpdatePlayerPos(Player player) {
	DrawTexture(player.sprite, 400, player.posY, WHITE);
	return;
}

int main ()
{
	SetUpGame();
	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Player Dino = {0, wabbit};
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// draw some text using the default font
		DrawText("Testing", 200,200,20,BLACK);

		UpdatePlayerPos(Dino);
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}