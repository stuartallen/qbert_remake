#include <iostream>

#include <SDL.h>
#include <stdio.h>

#include "board.h"
using namespace std;

//  Constructor 
Board::Board() {
    total_cubes = 0;
    cubes = new int*[BOARD_LEN];
    for(int i = 0; i < BOARD_LEN; i++) {
        cubes[i] = new int[BOARD_LEN - i];
        for(int j = 0; j < BOARD_LEN - i; j++) {
            cubes[i][j] = NO_TOUCH_COLOR;
            total_cubes++;
        }
    }
}

//  Updates the color at the input row and col  
void Board::update_color(int r, int c) {
    //  TODO this will work differently for higher levels   
    cubes[r][c] = FINAL_COLOR;
}

void Board::animate(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int i = 0; i < BOARD_LEN; i++) {
        for(int j = 0; j < BOARD_LEN - i; j++) {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_Rect rect;
            rect.x = ORIGIN_X + SQUARE_SIZE * i;
            rect.y = ORIGIN_Y + SQUARE_SIZE * j;
            rect.w = SQUARE_SIZE;
            rect.h = SQUARE_SIZE;
            SDL_RenderDrawRect(renderer, &rect);
            if(cubes[i][j] == NO_TOUCH_COLOR) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 250, 150, 0, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

//  returns if a row and column is in the board 
bool Board::in_board(int r, int c) {
    return r < BOARD_LEN && c < BOARD_LEN;
}

//  returns if all the colors are the final color   
bool Board::board_filled() {
    return correct_color >= total_cubes;
}

//  returns a reference to the cubes on the board   
int** Board::get_cubes() {
    return cubes;
}

//  prints the value of all the cubes in cubes  
void Board::print() {
    for(int i = 0; i < BOARD_LEN; i++) {
        for(int j = 0; j < BOARD_LEN - i; j++) {
            cout << cubes[i][j];
        }
        cout << endl;
    }
}

//  Destructor  
Board::~Board() {
    for(int i = 0; i < BOARD_LEN; i++) {
        delete [] cubes[i];
    }
    delete [] cubes;
}