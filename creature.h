//  Creatures are a parent class of all mobs and player
#ifndef CREATURE_H
#define CREATURE_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string.h>
#include "board.h"
using namespace std;

class Creature {
    protected:
        int row;
        int col;
        unsigned int x_pos;
        unsigned int y_pos;
        float start_time;
        float wait_time;
        Board* board;
        SDL_Renderer* renderer;
    public:
        //  TODO Make this include time
        //  Won't do anything here because constructors
        //  cannot be virtual
        Creature();
        Creature(Board*);
        
        //  virtual functions
        virtual void spawn() = 0;
        //  All derived classes have a move function but some will
        //  take different parameters
        virtual void animate();
        void set_screen_pos();

        void set_renderer(SDL_Renderer*);

        int get_row();
        int get_col();
        //  returns row and col concatenated
        int get_pos();
        bool on_board();
};

#endif