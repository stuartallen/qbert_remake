#ifndef BOARD_H
#define BOARD_H
#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//  TODO make Board the parent class of level class 
class Board {
    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int x_orig = 250;
        int y_orig = 250;
        const int BOARD_LEN = 7;

        const unsigned int SQUARE_WIDTH = 50;
        const double HEIGHT_DILATION = 0.75;

        const int NO_TOUCH_COLOR = 0;
        const int FINAL_COLOR = 1;

        SDL_Renderer* renderer;

        int** cubes;

        //  represents how many cubes are the final color   
        int correct_color;
        //  represents how many cubes there are total   
        int total_cubes;

        //  draw a trapezoid
    public:
        Board();
        ~Board();

        void draw_cube(unsigned int, unsigned int, unsigned int, unsigned int);
        void set_renderer(SDL_Renderer*);

        void animate();

        void set_screen_size(int, int);

        void update_color(int, int);
        bool in_board(int,int);
        bool board_filled();
        int** get_cubes();
        void print();

        int get_board_len();
        int get_x_orig();
        int get_y_orig();
};

#endif