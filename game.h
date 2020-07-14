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
        SpriteSheet* sprites;

        const int SPRITE_SWITCH_TIME = 100;

        const int QBERT_SPRITE_ID = 0;
        const int QBERT_X_SPRITE_POS = 116;
        const int QBERT_Y_SPRITE_POS = 0;
        const int QBERT_SPRITE_WIDTH = 30;
        const int QBERT_SPRITE_HEIGHT = 48;
        const int QBERT_SPRITE_FRAMES = 3;

        Board* board = nullptr;
        Player* player = nullptr;
        Creature** enemies = nullptr;

        void set_up_sprites();
    public:
        Game();
        Game(SDL_Renderer*);

};

#endif