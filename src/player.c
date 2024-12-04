#include "raylib.h"
#include "player.h"
#include "utility.h"


//Handles physics variables such as velocity and position
void UpdatePlayerPhysics(Player* player, float delta) {
	//Directly incrementing posY by gravity results in constant fall speed
	player->velocityY += GRAVITY*delta;
	player->posY += player->velocityY*delta;

	//Ground reached
	if (player->posY > GROUND_Y) {
		player->velocityY = 0;
		player->posY = GROUND_Y;
		player->frame_speed = 6;
		player->state = RUNNING;
	}
	//Jumping
	if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) & (player->state == RUNNING)) {
		player->velocityY -= GRAVITY/1.3;
		player->frame_speed *= 2;
		player->state = JUMPING;
	}
	player->hitbox.x = player->posY;
	return;
}
void UpdatePlayerAnim(Player *player) {
	player->frame_counter++;

	if (player->frame_counter >= (60/player->frame_speed)) {
		player->frame_counter = 0;
		player->current_frame++;
		player->current_frame %= 3; //Used to loop current_frame from 0 to 2
		player->frame_sheet.x = (float)player->current_frame*player->sprite.width/3;
	}
}

//Handles actual on-screen positon and animation (as opposed to UpdatePlayerPhysics)
void UpdatePlayer(Player *player) {
	DrawTextureRec(player->sprite, player->frame_sheet, (Vector2){POSX, player->posY - player->sprite.height}, WHITE);
	return;
}