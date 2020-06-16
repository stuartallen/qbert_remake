#ifndef BOARD_H
#define BOARD_H
#include <iostream>

#include <SDL.h>
#include <stdio.h>

using namespace std;

//  TODO make Board the parent class of level class 
class Board {
    private:
        const int ORIGIN_X = 250;
        const int ORIGIN_Y = 250;
        const int SQUARE_SIZE = 50;
        const int BOARD_LEN = 7;

        const int NO_TOUCH_COLOR = 0;
        const int FINAL_COLOR = 1;

        int** cubes;

        //  represents how many cubes are the final color   
        int correct_color;
        //  represents how many cubes there are total   
        int total_cubes;
        //  TODO create array of platform positions 
    public:
        Board();
        ~Board();

        void animate(SDL_Renderer*);

        void update_color(int, int);
        bool in_board(int,int);
        bool board_filled();
        int** get_cubes();
        void print();
};


#endif