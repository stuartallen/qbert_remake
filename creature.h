//  Creatures are a parent class of all mobs and player
#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string.h>
#include "board.h"
using namespace std;

class Creature {
    protected:
        int row;
        int col;
        float start_time;
        float wait_time;
        Board* board;
    public:
        //  TODO Make this include time
        //  Won't do anything here because constructors
        //  cannot be virtual
        Creature();
        Creature(Board*);
        
        //  virtual functions
        virtual void spawn() = 0;
        virtual void move() = 0;

        int get_row();
        int get_col();
        //  returns row and col concatenated
        int get_pos();
        bool on_board();
};

#endif