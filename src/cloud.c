#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400
#define GROUND_Y 300
#define MAX_CLOUDS 3
#define CLOUD_SPEED_MULTIPLIER 0.3f
#define CLOUD_PATH "Assets/Other/Cloud.png"

typedef struct {
    Vector2 position;
    bool active;
    float speed;
} Cloud;

void InitializeCloud(Cloud* cloud) {
    cloud->position.x = WINDOW_WIDTH;
    cloud->position.y = GetRandomValue(50, GROUND_Y - 100);
    cloud->speed = GetRandomValue(100, 200) * CLOUD_SPEED_MULTIPLIER;
    cloud->active = true;
}

void UpdateCloud(Cloud* cloud, float deltaTime) {
    if (cloud->active) {
        cloud->position.x -= cloud->speed * deltaTime;
        if (cloud->position.x < -100) {
            InitializeCloud(cloud);
        }
    }
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cloud Test");
    SetTargetFPS(60);

    // Load cloud texture
    Texture2D cloudTexture = LoadTexture(CLOUD_PATH);

    // Initialize clouds
    Cloud clouds[MAX_CLOUDS] = { 0 };
    for (int i = 0; i < MAX_CLOUDS; i++) {
        InitializeCloud(&clouds[i]);
        clouds[i].position.x += i * (WINDOW_WIDTH / MAX_CLOUDS);
    }

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update clouds
        for (int i = 0; i < MAX_CLOUDS; i++) {
            UpdateCloud(&clouds[i], deltaTime);
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw clouds
        for (int i = 0; i < MAX_CLOUDS; i++) {
            if (clouds[i].active) {
                DrawTexture(cloudTexture, clouds[i].position.x, clouds[i].position.y, WHITE);
            }
        }

        // Draw additional debug information
        for (int i = 0; i < MAX_CLOUDS; i++) {
            DrawText(TextFormat("Cloud %d: X = %.2f, Y = %.2f, Speed = %.2f",
                i, clouds[i].position.x, clouds[i].position.y, clouds[i].speed),
                10, 20 + (i * 30), 20, BLACK);
        }

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(cloudTexture);
    CloseWindow();

    return 0;
}