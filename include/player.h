#ifndef PLAYER
#define PLAYER
#include "raylib.h"

//Variables & Constants
#define GRAVITY 1000.0f
#define INITIALJUMPFORCE 600.0f
#define ADDJUMPFORCE 400.0f
#define MAXJUMPTIME 2
#define POSX 200
#define PLAYER_MARGIN_X 20     // Reduces player hitbox width by 20px on each side
#define PLAYER_MARGIN_Y 10     // Reduces player hitbox height by 10px top and bottom

extern bool showHitboxes;    // Just declare it

typedef enum {
		JUMPING,
		RUNNING,
		DEAD
} Player_state;

//Player Object
typedef struct {
	float posY;
	float velocityY;
	Rectangle hitbox;
	Texture sprite;
	Player_state state;
	//Animation components
	int frame_counter; //Counter allowing for frame-changing, independently from FPS
	int frame_speed; //Animation frames per second
	int current_frame;
	Rectangle frame_sheet;
} Player;


//Handles physics variables such as velocity and position
void UpdatePlayerPhysics(Player *player, float delta);
void UpdatePlayerAnim(Player *player);
//Handles actual on-screen positon and animation (as opposed to UpdatePlayerPhysics)
void UpdatePlayer(Player *player); 
void UpdatePlayerHitbox(Player* player);
#endif