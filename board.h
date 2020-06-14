#ifndef BOARD_H
#define BOARD_H
#include <iostream>
using namespace std;

//  TODO make Board the parent class of level class 
class Board {
    private:

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
        //  TODO add animate function   
        void update_color(int, int);
        bool in_board(int,int);
        bool board_filled();
        int** get_cubes();
        void print();
};


#endif