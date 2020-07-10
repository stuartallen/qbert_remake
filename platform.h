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

        int x_pos;
        int y_pos;

        Board* board;
        SpriteSheet* sprites;
    public:
        Platform(Board*, SpriteSheet*);
        ~Platform();

        void set_loc(int, int);
        void animate();
        void init_transport();
        void transport();

        int* get_pos();
};

#endif