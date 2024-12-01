#include "raylib.h"
#include "player.h"

//Handles physics variables such as velocity and position
void UpdatePlayerPhysics(Player* player, float delta) {
	//Directly incrementing posY by gravity results in constant fall speed
	player->velocityY += GRAVITY*delta;
	player->posY += player->velocityY*delta;

	//Ground reached
	if (player->posY > GROUND_Y) {
		player->velocityY = 0;
		player->posY = GROUND_Y;
		player->state = RUNNING;
	}
	//Jumping
	if (IsKeyPressed(KEY_SPACE) & (player->state == RUNNING)) {
		player->velocityY -= GRAVITY/1.2;
		player->state = JUMPING;
	}
	return;
}
//Handles actual on-screen positon (as opposed to UpdatePlayerPhysics)
void UpdatePlayerPos(Player *player) {
	DrawTexture(player->sprite, POSX, player->posY - player->sprite.height, WHITE);
	return;
}