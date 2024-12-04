#ifndef UTILITY
#define UTILITY
#include "raylib.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 800
#define GROUND_Y 600
#define MAXCLOUDS 4

#define CACTUSHEIGHT 10
#define CACTUSWIDTH 5

//Global scope
extern float global_velocity; //DO NOT CHANGE TO CONST : it will vary
typedef enum _Game_state {MENU, GAME, GAMEOVER} Game_state;
extern Game_state game_state;


//Scenery types and components
typedef struct {
	Vector2 position;
	float velocity;
	Texture sprite;
} Cloud;

extern Cloud clouds[MAXCLOUDS];
extern float cloud_velocity;

typedef struct Obstacle {
    Vector2 position;
    Texture2D texture;
    Rectangle hitbox;
} Obstacle;
extern Obstacle cactus;


void SetUpGame(); //Sets up environment

void InitializeCloud(Cloud* cloud_arr);
void UpdateCloudPhysics(Cloud* cloud, float delta);
void DrawClouds(Cloud cloud[], float delta);


void InitializeObstacle(Obstacle* obstacle, Texture2D Texture);
void UpdateObstacle(Obstacle* obstacle, float deltaTime);


void DrawScenery(float delta); //Draws ground, clouds

#endif