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
//la commande pour gcc c'est ce truc :  gcc -o game main.c player.c utility.c -I../include -lraylib -lGL -lm -lpthread -ldl -lX11

#include "raylib.h"

//Personal libraries
#include "utility.h"
#include "player.h"


int main ()
{
	SetUpGame();
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	
	Player Dino = {0, 0, wabbit, JUMPING};
	
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float delta = GetFrameTime();	

		UpdatePlayerPhysics(&Dino, delta);
		// drawing
		BeginDrawing();

		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// draw some text using the default font
		DrawText("To do : Placing elements at right positions\nAnimations\nSFX\nMusic\nMenu", 200,200,20,BLACK);

		UpdatePlayerPos(&Dino);
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}