//  Creatures are a parent class of all mobs and player
#ifndef CREATURE_H
#define CREATURE_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string.h>
#include <cmath>
#include "board.h"
#include "sound.h"
using namespace std;

class Creature {
    protected:
        int old_row;
        int old_col;
        int row;
        int col;

        int jump_x;
        int jump_y;
        bool jumping;
        const int JUMP_TIME = 500;
        const int JUMP_HEIGHT = 100;
        unsigned int start_jump_time;
        Sound* jump_sound = nullptr;

        int x_pos;
        int y_pos;

        int** bez_pts;
        Board* board;
        SDL_Renderer* renderer;
    public:
        //  TODO Make this include time
        //  Won't do anything here because constructors
        //  cannot be virtual
        Creature();
        Creature(Board*);
        ~Creature();
        
        //  virtual functions
        virtual void spawn() = 0;
        virtual void animate();
        void set_screen_pos();

        void move(int, int);
        void init_jump(int, int);
        //  For non player objects just implement the code already there
        virtual void jump();

        void set_renderer(SDL_Renderer*);
        void set_jump_sound(Sound*);

        int get_row();
        int get_col();
        //  returns row and col concatenated
        int get_pos();
        bool on_board();
};

#endif