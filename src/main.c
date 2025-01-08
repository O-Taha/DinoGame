/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "utility.h" 
#include "player.h"
#include <stdbool.h>

// Toggle hitboxes with the H key (debug)
bool showHitboxes = false;
Game_state game_state = MENU;
int score = 0;
int highScore = 0;

int main() {
    // Initialize the game; among others
    SetUpGame();
    InitAudioDevice();

    // Loading assets
    Texture buns_sprite =  LoadTexture("Buns_Spritesheet.png");
    Texture FG = LoadTexture("CityFG.png");
    Texture BG = LoadTexture("CityBG.png");
    Sound music_intro = LoadSound("Music/NES_Shooter_Music_by_SketchyLogic_BossIntro.wav");
    Music title_screen_music = LoadMusicStream("Music/my_street_by_congusbongus.wav");
    Music bg_music = LoadMusicStream("Music/NES_Shooter_Music_by_SketchyLogic_BossMain.wav");
    Music game_over_music = LoadMusicStream("Music/two_left_socks_by_congusbongus.wav");
    Sound jump_sound = LoadSound("SFX/Jump.wav");
    Sound death_sound = LoadSound("SFX/hitHurt.wav");
    PlayMusicStream(title_screen_music);
    PlayMusicStream(bg_music);
    PlayMusicStream(game_over_music);

    // Automatic sprite loading system
    Texture obstacle_sprites[OBSTACLETYPES];
    FilePathList obstacle_paths = LoadDirectoryFiles("./Obstacles");
    for (int i = 0; i < obstacle_paths.count; i++) {
        obstacle_sprites[i] = LoadTexture(obstacle_paths.paths[i]);
    }

    // Initialize player
    Rectangle current_frame_sheet = {0.0, 0.0, (float)buns_sprite.width / 3.0, (float)buns_sprite.height};
    Rectangle buns_hitbox = {POSX, GROUND_Y - buns_sprite.height, current_frame_sheet.width, current_frame_sheet.height};
    Player buns = {0, GROUND_Y - buns_sprite.height, buns_hitbox, buns_sprite, JUMPING, 0, 6, 0, current_frame_sheet};

    // Initialize scenery
    InitializeCloud(clouds);
    InitializeObstacle(&hazard, obstacle_sprites);

    // Game loop
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        if (IsKeyPressed(KEY_H)) {
            showHitboxes = !showHitboxes;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        if (!(IsWindowHidden() || IsWindowMinimized() || !IsWindowFocused())) DrawScenery(FG, BG, delta); //When not focused, bugs related to music and delta are avoided by skipping computation


        switch (game_state) {
            case MENU:
                DrawText("Buns Rush!", SCREENWIDTH / 2 - MeasureText("Buns Rush!", 50) / 2, SCREENHEIGHT / 4, 50, BLACK);
                DrawText("Press SPACE to start", SCREENWIDTH / 2 - MeasureText("Press SPACE to start", 30) / 2, SCREENHEIGHT / 2, 30, BLACK);
                UpdateMusicStream(title_screen_music);

                if (IsKeyPressed(KEY_SPACE)) {
                    if (!highScore) PlaySound(music_intro); //Play the intro music only if it's the first time!
                    game_state = GAME;
                    UnloadMusicStream(title_screen_music);
                }
                break;

            case GAME:
                if (!IsSoundPlaying(music_intro)) UpdateMusicStream(bg_music);
                UpdatePlayer(&buns, jump_sound);
                UpdateObstacle(&hazard, obstacle_sprites, delta);

                // Update score (increase by 1 point every second)
                score += (int)(60 * delta);
                DrawText(TextFormat("Score: %d", score), 20, 20, 30, BLACK);
                DrawText(TextFormat("High Score: %d", highScore), 20, 60, 20, BLACK);

                if (CheckCollisionRecs(buns.hitbox, hazard.hitbox)) {
                    buns.state = DEAD;
                    if (score > highScore) {
                        highScore = score;
                    }
                    game_state = GAMEOVER;
                    PlaySound(death_sound);
                    SeekMusicStream(game_over_music, 0.0);
                }

                if (showHitboxes) {
                    DrawRectangleLines(buns.hitbox.x, buns.hitbox.y, buns.hitbox.width, buns.hitbox.height, RED);
                    DrawRectangleLines(hazard.hitbox.x, hazard.hitbox.y, hazard.hitbox.width, hazard.hitbox.height, RED);
                }
                break;

            case GAMEOVER:
                DrawText("Game Over!", SCREENWIDTH / 2 - MeasureText("Game Over!", 50) / 2, SCREENHEIGHT / 3, 50, BLACK);
                DrawText(TextFormat("Final Score: %d", score), SCREENWIDTH / 2 - MeasureText(TextFormat("Final Score: %d", score), 40) / 2, SCREENHEIGHT / 3 + 70, 40, BLACK);
                DrawText(TextFormat("High Score: %d", highScore), SCREENWIDTH / 2 - MeasureText(TextFormat("High Score: %d", highScore), 30) / 2, SCREENHEIGHT / 3 + 120, 30, BLACK);
                DrawText("\n Press SPACE to restart\n     Press ESC to quit", SCREENWIDTH / 2 - MeasureText("\n Press SPACE to restart", 30) / 2, SCREENHEIGHT / 2, 30, BLACK);
                UpdateMusicStream(game_over_music);
                if (IsKeyPressed(KEY_SPACE)) {
                    game_state = GAME;
                    buns.state = JUMPING;
                    buns.posY = GROUND_Y - buns.sprite.height;
                    buns.velocityY = 0;
                    score = 0;
                    InitializeObstacle(&hazard, obstacle_sprites);
                }
                break;
            
        }

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(buns_sprite);
    for (int i = 0; i < MAXCLOUDS; i++) {
        UnloadTexture(clouds[i].sprite);
    }
    for (int i = 0; i < obstacle_paths.count; i++) {
        UnloadTexture(obstacle_sprites[i]);
    }
    UnloadDirectoryFiles(obstacle_paths);
    UnloadSound(music_intro);
    UnloadMusicStream(bg_music);
    UnloadMusicStream(game_over_music);
    UnloadSound(jump_sound);
    UnloadSound(death_sound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
