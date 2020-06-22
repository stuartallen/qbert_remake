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
    cubes[1][1] = FINAL_COLOR;
}



void Board::set_renderer(SDL_Renderer* in_r) {
    renderer = in_r;
}

//  Updates the color at the input row and col  
void Board::update_color(int r, int c) {
    //  TODO this will work differently for higher levels   
    cubes[r][c] = FINAL_COLOR;
}

//  Draw one cube. Inputs should be center of cube
void Board::draw_cube(unsigned int x, unsigned int y) {
    //  points are labeled clockwise starting from 10'o'clock
    Sint16** points = new Sint16*[7];
    for(int i = 0; i < 6; i++) {
        points[i] = new Sint16[2];
        points[i][0] = SQUARE_WIDTH * cos(2.0/6 * M_PI * i + 7*M_PI/6) + x;
        points[i][1] = SQUARE_WIDTH*HEIGHT_DILATION * sin(2.0/6 * M_PI * i + 7*M_PI/6) + y;
    }
    points[6] = new Sint16[2];
    points[6][0] = x;
    points[6][1] = y;

    //  Top
    Sint16 points_x_top[] = {points[0][0], points[1][0], points[2][0], points[6][0]};
    Sint16 points_y_top[] = {points[0][1], points[1][1], points[2][1], points[6][1]};               
    // args are: renderer, x coords, y coords, point #, and rgba
    filledPolygonRGBA(renderer, points_x_top, points_y_top, 4, 250, 150, 0, 250);
    //  Bottom Right
    Sint16 points_x_right[] = {points[2][0], points[3][0], points[4][0], points[6][0]};
    Sint16 points_y_right[] = {points[2][1], points[3][1], points[4][1], points[6][1]};               
    filledPolygonRGBA(renderer, points_x_right, points_y_right, 4, 0, 250, 150, 250);
    //  Bottom Left
    Sint16 points_x_left[] = {points[0][0], points[5][0], points[4][0], points[6][0]};
    Sint16 points_y_left[] = {points[0][1], points[5][1], points[4][1], points[6][1]};               
    // args are: renderer, x coords, y coords, point #, and rgba
    filledPolygonRGBA(renderer, points_x_left, points_y_left, 4, 150, 0, 250, 250);

    for(int i = 0; i < 7; i++) {
        delete [] points[i];
    }
    delete [] points;
}

//  draws all the platforms
void Board::animate() {
    SDL_RenderClear(renderer);
    const unsigned int x_orig = SCREEN_WIDTH/2;
    const unsigned int y_orig = SCREEN_HEIGHT/4;
    const unsigned int x_mov = SQUARE_WIDTH * cos(2.0/6 * M_PI * 3 + 7*M_PI/6);
    const unsigned int y_mov = SQUARE_WIDTH*HEIGHT_DILATION * (sin(2.0/6 * M_PI * 4 + 7*M_PI/6) + sin(2.0/6 * M_PI * 3 + 7*M_PI/6));
    for(int i = 0; i < BOARD_LEN; i++) {
        for(int j = 0; j < BOARD_LEN - i; j++) {
            unsigned int x_pos = x_orig + x_mov * i - x_mov * j;
            unsigned int y_pos = y_orig + y_mov * i + y_mov * j;
            if(cubes[i][j] == NO_TOUCH_COLOR) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 250, 150, 0, 255);
            }
            draw_cube(x_pos, y_pos);
        }
    }
}

void Board::set_screen_size(int in_w, int in_h) {
    SCREEN_WIDTH = in_w;
    SCREEN_HEIGHT = in_h;
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