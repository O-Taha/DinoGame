#ifndef PLAYER
#define PLAYER
#include "raylib.h"
//Constants
#define GRAVITY 1000
#define GROUND_Y 600
#define POSX 200

typedef enum {
		JUMPING,
		RUNNING,
		DEAD
	} player_state;

//Player Object
typedef struct {
	float posY;
	float velocityY;
	Texture sprite;
	player_state state;
} Player;

void UpdatePlayerPos(Player *player);
void UpdatePlayerPhysics(Player *player, float delta);
#endif