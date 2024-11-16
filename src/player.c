#include "raylib.h"
#include "player.h"

//Handles physics variables such as velocity and position
void UpdatePlayerPhysics(Player* player, float delta) {
	//Directly incrementing posY by gravity results in constant fall speed
	player->velocityY += GRAVITY*delta;
	player->posY += player->velocityY*delta;
	return;
}
//Handles actual on-screen positon (as opposed to theo)
void UpdatePlayerPos(Player *player) {
	if (player->posY > GROUND_Y) {
		player->velocityY = 0;
		player->posY = GROUND_Y;
	}
	DrawTexture(player->sprite, 1000, player->posY, WHITE);
	return;
}