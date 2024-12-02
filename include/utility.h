#ifndef UTILITY
#define UTILITY
#include "raylib.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 800
#define MAXCLOUDS 4

extern float global_velocity; //DO NOT CHANGE TO CONST : it will vary

typedef struct {
	Vector2 position;
	float velocity;
	Texture sprite;
} Cloud;

extern Cloud clouds[MAXCLOUDS];
extern float cloud_velocity;

void SetUpGame(); //Sets up environment

void InstantiateCloud(Cloud* cloud_arr);
void UpdateCloudPhysics(Cloud* cloud, float delta);
void DrawClouds(Cloud cloud[], float delta);

void DrawScenery(float delta); //Draws ground, clouds

#endif