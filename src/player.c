#include "raylib.h"
#include "player.h"
#include "utility.h"


float jump_time = 0;

//Handles physics variables such as velocity and position
void UpdatePlayerPhysics(Player* player, float delta) {

	//Ground reached
	if (player->posY > GROUND_Y) {
		player->velocityY = 0;
		player->posY = GROUND_Y;
		player->frame_speed = 6;
		player->state = RUNNING;
	}
	//Jumping
	if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && (player->state == RUNNING)) {
		player->velocityY = -INITIALJUMPFORCE;
		jump_time = 0;
		player->frame_speed *= 2;
		player->state = JUMPING;
	}
	if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && ((player->velocityY < 0) && (jump_time < MAXJUMPTIME))) player->velocityY -= ADDJUMPFORCE*delta;

	jump_time += delta;
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
	float deltaTime = GetFrameTime();
	DrawTextureRec(player->sprite, player->frame_sheet, (Vector2){POSX, player->posY - player->sprite.height}, WHITE);
    UpdatePlayerPhysics(player, deltaTime);
    UpdatePlayerAnim(player);
    UpdatePlayerHitbox(player);  // Add this line
	return;
}

void UpdatePlayerHitbox(Player* player) {
    player->hitbox = (Rectangle){
        POSX + PLAYER_MARGIN_X,                          // X position with margin
        player->posY - player->sprite.height + PLAYER_MARGIN_Y,  // Y position adjusted to match sprite
        (float)player->sprite.width/3 - (PLAYER_MARGIN_X * 2),  // Width with margins
        (float)player->sprite.height - (PLAYER_MARGIN_Y * 2)    // Height with margins
    };
}
