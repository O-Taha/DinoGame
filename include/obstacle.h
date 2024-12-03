// obstacle.h
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Obstacle {
    Vector2 position;
    bool active;
    Texture2D texture;
    Rectangle hitbox;
} Obstacle;

void InitializeObstacle(Obstacle* obstacle, Texture2D cactusTexture);
void UpdateObstacle(Obstacle* obstacle, float deltaTime, float scrollSpeed);
bool IsObstacleOffScreen(Obstacle* obstacle);

#endif // OBSTACLE_H
