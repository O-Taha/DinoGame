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
} Player_state;

//Player Object
typedef struct {
	float posY;
	float velocityY;
	Texture sprite;
	Player_state state;
} Player;


//Handles physics variables such as velocity and position
void UpdatePlayerPhysics(Player *player, float delta);
//Handles actual on-screen positon (as opposed to UpdatePlayerPhysics)
void UpdatePlayerPos(Player *player); 
#endif