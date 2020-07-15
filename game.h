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

#define QBERT_JUMP "jump-9.wav"
#define BALL_JUMP "jump-5.wav"
#define SNAKE_JUMP "jump-4.wav"
#define COLLIDE "explode-3.wav"
#define FALL_LOSE "lose-5.wav"

#define SPRITE_SHEET "QBert3Sheet1.bmp"

class Game {
    private:
        SDL_Renderer* renderer;
        SpriteSheet** sprites;

        int screen_width;
        int screen_height;

        const int QBERT_SPRITE_ID = 0;
        const int QBERT_X_SPRITE_POS = 116;
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

        const int QBERT_JUMP_SOUND_ID = 0;
        const int BALL_JUMP_SOUND_ID = 1;
        const int COLLIDE_SOUND_ID = 2;
        const int FALL_SOUND_ID = 3;
        const int SNAKE_JUMP_SOUND_ID = 4;

        Board* board;
        Player* player = nullptr;
        Creature** enemies = nullptr;
        const int NUM_ENEMIES = 2;
        Platform** platforms = nullptr;
        const int NUM_PLATFORMS = 2;
        Sound** sounds = nullptr;

        bool game_going = true;

        void set_up_sprites();
        void set_up_enemies();
        void set_up_qbert();
        void set_up_platforms();
        void set_up_sounds();

        void handle_key_press(SDL_Event&);
    public:
        Game();
        Game(SDL_Renderer*, int, int);
        ~Game();

        void loop();

        bool going();
};

#endif