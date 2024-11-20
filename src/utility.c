#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "utility.h"

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

void DrawScenery() {
	
} 
