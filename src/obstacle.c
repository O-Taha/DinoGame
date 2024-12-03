#include "raylib.h"
#include "obstacle.h"
#include<stdio.h>

#define SCREENWIDTH 1280
#define GROUND_Y 600
#define CACTUS_MARGIN_X 10
#define CACTUS_MARGIN_Y 5




void InitializeObstacle(Obstacle* obstacle, Texture2D cactusTexture) {
    // Set the cactus texture
    obstacle->texture = cactusTexture;

    // Position the cactus off-screen to the far right, aligned with the ground
    obstacle->position = (Vector2){
        SCREENWIDTH + CACTUS_MARGIN_X,  // Spawn off-screen to the right (same as clouds)
        GROUND_Y - cactusTexture.height // Align the bottom of the cactus with the ground
    };

    // Mark the obstacle as active
    obstacle->active = true;
}




void UpdateObstacle(Obstacle* obstacle, float deltaTime, float scrollSpeed) {
    if (obstacle->active) {
        obstacle->position.x -= scrollSpeed * deltaTime;
        obstacle->hitbox.x = obstacle->position.x; // Update hitbox position
    }
}

bool IsObstacleOffScreen(Obstacle* obstacle) {
    return obstacle->position.x + obstacle->texture.width < 0;
}
