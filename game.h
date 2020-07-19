#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

#include "creature.h"
#include "ball.h"
#include "snake.h"
#include "player.h"
#include "platform.h"
#include "sound.h"
#include "spriteSheet.h"
#include "board.h"

#define QBERT_JUMP "resources/jump-9.wav"
#define BALL_JUMP "resources/jump-5.wav"
#define SNAKE_JUMP "resources/jump-4.wav"
#define COLLIDE "resources/explode-3.wav"
#define FALL_LOSE "resources/lose-5.wav"
#define PRE_SPAWN "resources/cancel-1.wav"
#define WIN "resources/win-1.wav"

#define SPRITE_SHEET "resources/QBert3Sheet1.bmp"

class Game {
    private:
        SDL_Renderer* renderer = nullptr;
        SpriteSheet** sprites = nullptr;

        int screen_width;
        int screen_height;

        const int NUM_SPRITES = 5;

        const int QBERT_SPRITE_ID = 0;
        const int QBERT_X_SPRITE_POS = 106;
        const int QBERT_Y_SPRITE_POS = 0;
        const int QBERT_SPRITE_WIDTH = 30;
        const int QBERT_SPRITE_HEIGHT = 48;
        const int QBERT_SPRITE_FRAMES = 3;
        const int QBERT_SPRITE_SWITCH_TIME = 100;

        const int RED_BALL_SPRITE_ID = 1;
        const int RED_BALL_X_SPRITE_POS = 122;
        const int RED_BALL_Y_SPRITE_POS = 98;
        const int RED_BALL_SPRITE_WIDTH = 25;
        const int RED_BALL_SPRITE_HEIGHT = 32;
        const int RED_BALL_SPRITE_FRAMES = 3;
        const int RED_BALL_SPRITE_SWITCH_TIME = 200;

        const int SNAKE_BALL_SPRITE_ID = 2;
        const int SNAKE_BALL_X_SPRITE_POS = 193;
        const int SNAKE_BALL_Y_SPRITE_POS = 98;
        const int SNAKE_BALL_SPRITE_WIDTH = 30;
        const int SNAKE_BALL_SPRITE_HEIGHT = 32;
        const int SNAKE_BALL_SPRITE_FRAMES = 3;
        const int SNAKE_BALL_SPRITE_SWITCH_TIME = 200;

        const int SNAKE_SPRITE_ID = 3;
        const int SNAKE_X_SPRITE_POS = 35;
        const int SNAKE_Y_SPRITE_POS = 136;
        const int SNAKE_SPRITE_WIDTH = 40;
        const int SNAKE_SPRITE_HEIGHT = 60;
        const int SNAKE_SPRITE_FRAMES = 4;
        const int SNAKE_SPRITE_SWITCH_TIME = 200;
        const int SNAKE_SPRITE_SECOND_LAYER_OFFSET = 40;

        const int PLAT_SPRITE_ID = 4;
        const int PLAT_X_SPRITE_POS = 80;
        const int PLAT_Y_SPRITE_POS = 1000;
        const int PLAT_SPRITE_WIDTH = 40;
        const int PLAT_SPRITE_HEIGHT = 20;
        const int PLAT_SPRITE_FRAMES = 3;
        const int PLAT_SPRITE_SWITCH_TIME = 100;

        const int NUM_SOUNDS = 7;
        const int QBERT_JUMP_SOUND_ID = 0;
        const int BALL_JUMP_SOUND_ID = 1;
        const int COLLIDE_SOUND_ID = 2;
        const int FALL_SOUND_ID = 3;
        const int SNAKE_JUMP_SOUND_ID = 4;
        const int PRE_SPAWN_SOUND_ID = 5;
        const int WIN_SOUND_ID = 6;

        const int SNAKE_ENEMY_ID = 1;
        const int BALL_ENEMY_ID = 0;

        Board* board = nullptr;
        Player* player = nullptr;
        Creature** enemies = nullptr;
        const int NUM_ENEMIES = 3;
        Platform** platforms = nullptr;
        const int NUM_PLATFORMS = 2;
        Sound** sounds = nullptr;

        bool game_going = true;

        void set_up_sprites();
        void set_up_enemies();
        void set_up_qbert();
        void set_up_platforms();
        void set_up_sounds();

        

        int snake_timer_start = 0;
        const int SNAKE_WAIT = 7500;
        bool snake_spawn_sound_played = false;
        int ball_timer_start = 0;
        const int BALL_WAIT = 2000;
        bool ball_spawn_sound_played = false;
        const int MINI_TIMER_WAIT = 500;

        int won_or_lost = 1;
    public:
        Game();
        Game(SDL_Renderer*, int, int);
        ~Game();

        void loop(SDL_Event*);

        void update_snake_timer();
        void update_ball_timer();

        bool going();

        void check_won_lost();

        void handle_key_press(SDL_Event*);
};

#endif