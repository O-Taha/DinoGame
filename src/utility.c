#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "utility.h"


//Initialising variables
float global_velocity = 400.0f;
float cloud_velocity = 10;
Cloud clouds[MAXCLOUDS];
Obstacle hazard;

//Sets up environment
void SetUpGame() {
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Buns Rush!");
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);
	return;
}

void InitializeCloud(Cloud* cloud_arr) {
	for (int i = 0; i < MAXCLOUDS; i++) {
		Cloud cloud;
		cloud.position.x = SCREENWIDTH;
		cloud.position.y = GetRandomValue(0, GROUND_Y/2);
		cloud.velocity = GetRandomValue(cloud_velocity - cloud_velocity/2, cloud_velocity + cloud_velocity/2);
		cloud.sprite = LoadTexture("Cloud.png");
		cloud_arr[i] = cloud;
	}
}

void UpdateCloudPhysics(Cloud* cloud_arr, float delta) {
	for (int i = 0; i < MAXCLOUDS; i++) {
		cloud_arr[i].position.x -= cloud_arr[i].velocity * delta;

        if (cloud_arr[i].position.x < -cloud_arr[i].sprite.width) { //if the edge of the screen is reached
			cloud_arr[i].position.x = SCREENWIDTH;
			cloud_arr[i].position.y = GetRandomValue(0, GROUND_Y/2);
			cloud_arr[i].velocity = GetRandomValue(cloud_velocity - cloud_velocity/2, cloud_velocity + cloud_velocity/2);
        }
    }
}

void DrawClouds(Cloud* cloud_arr, float delta) {
	for (int i = 0; i < MAXCLOUDS; i++) {
		UpdateCloudPhysics(cloud_arr, delta);
        DrawTexture(cloud_arr[i].sprite, cloud_arr[i].position.x, cloud_arr[i].position.y, WHITE);
	}

}

void InitializeObstacle(Obstacle* obstacle, Texture obstacle_textures[]) {
    // Set the obstacle texture
    obstacle->texture = obstacle_textures[GetRandomValue(0, OBSTACLETYPES-1)];
	obstacle->hitbox = (Rectangle){SCREENWIDTH, GROUND_Y - obstacle->texture.height, obstacle->texture.width, obstacle->texture.height};
    // Position the obstacle off-screen to the far right, aligned with the ground
    obstacle->position = (Vector2){
        SCREENWIDTH,  // Spawn off-screen to the right (same as clouds)
        GROUND_Y - obstacle->texture.height // Align the bottom of the obstacle with the ground
    };
}


void UpdateObstacle(Obstacle* obstacle, Texture obstacle_textures[], float delta) {
    obstacle->position.x -= global_velocity * delta; // Update hitbox position
    obstacle->hitbox.x = obstacle->position.x;
	obstacle->hitbox.y = obstacle->position.y;
	if (obstacle->position.x + obstacle->texture.width < 0) {
		InitializeObstacle(obstacle, obstacle_textures);
    }
}

//Draws ground, clouds
void DrawScenery(float delta) {
	DrawLine(0, GROUND_Y, SCREENWIDTH, GROUND_Y, BLACK);
	DrawClouds(clouds, delta);
	if (game_state == GAME) DrawTexture(hazard.texture, hazard.position.x, hazard.position.y, WHITE);;
}