#ifndef PLAYER
#define PLAYER
#include "raylib.h"
//Constants
#define GRAVITY 100
#define GROUND_Y 300

//Player Object
typedef struct {
	float posY;
	float velocityY;
	Texture sprite;
} Player;

void UpdatePlayerPos(Player *player);
void UpdatePlayerPhysics(Player *player, float delta);
#endif