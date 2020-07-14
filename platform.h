#ifndef PLATFORM_H
#define PLATFORM_H

#include "board.h"
#include "spriteSheet.h"

#include <iostream>
#include <cstdlib>
using namespace std;

class Platform {
    private:
        bool used = false;
        int row;
        int col;
        int** bez_pts;

        int x_pos;
        int y_pos;

        Board* board;
        SpriteSheet* sprites;

        const int JUMP_HEIGHT = 100;
        const int MOVE_TIME = 2000;
        bool start_move;
        bool moving = false;
        int start_move_time;
        void set_bez_pts();
        void move();
    public:
        Platform(Board*, SpriteSheet*);
        ~Platform();

        void set_loc(int, int);
        void animate();

        int* get_pos();
        int get_row();
        int get_col();
        void start_moving();
};

#endif