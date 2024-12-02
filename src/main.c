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

//Personal libraries
#include "utility.h"
#include "player.h"


int main ()
{
	SetUpGame();

	Texture buns_sprite = LoadTexture("Buns_Spritesheet.png");
	Rectangle current_frame_sheet = {0.0, 0.0, (float)buns_sprite.width/3.0, (float)buns_sprite.height};

	Player buns = {0, 0, buns_sprite, JUMPING, 0, 6, 0, current_frame_sheet};
	
	InstantiateCloud(clouds);

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float delta = GetFrameTime();	
		DrawScenery(delta);
	
		UpdatePlayerPhysics(&buns, delta);
		UpdatePlayerAnim(&buns);
		// drawing
		BeginDrawing();
		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(SKYBLUE);

		// draw some text using the default font
		DrawText("To do : Placing elements at right positions\nSpawning hazards\nAnimations\nSFX\nMusic\nMenu", 200,200,20,BLACK);

		UpdatePlayer(&buns);
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(buns_sprite);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}