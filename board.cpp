#include "board.h"
using namespace std;

//  Constructor 
Board::Board() {
    SQUARE_WIDTH = 50;
    total_cubes = 0;
}

void Board::set_renderer(SDL_Renderer* in_r) {
    NO_TOUCH_COLOR = 0;
    FINAL_COLOR = 1;
    renderer = in_r;
    SQUARE_WIDTH = 50;
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
    if(cubes[r][c] == 0) {
        correct_color++;
    }
    cubes[r][c] = FINAL_COLOR;
}

//  Draw one cube. Inputs should be center of cube
void Board::draw_cube(unsigned int x, unsigned int y, unsigned int row, unsigned int col) {
    //  points are labeled clockwise starting from 10'o'clock
    Sint16** points = new Sint16*[7];
    for(int i = 0; i < 6; i++) {
        points[i] = new Sint16[2];
        points[i][0] = (Sint16)(SQUARE_WIDTH * cos(2.0/6 * M_PI * i + 7*M_PI/6)) + x;
        points[i][1] = (Sint16)(SQUARE_WIDTH*HEIGHT_DILATION * sin(2.0/6 * M_PI * i + 7*M_PI/6)) + y;
    }
    points[6] = new Sint16[2];
    points[6][0] = x;
    points[6][1] = y;

    //  Top
    Sint16 points_x_top[] = {points[0][0], points[1][0], points[2][0], points[6][0]};
    Sint16 points_y_top[] = {points[0][1], points[1][1], points[2][1], points[6][1]};               
    // args are: renderer, x coords, y coords, point #, and rgba
    if(cubes[row][col] == 0) {
        filledPolygonRGBA(renderer, points_x_top, points_y_top, 4, 100, 200, 100, 250);
    } else {
        filledPolygonRGBA(renderer, points_x_top, points_y_top, 4, 0, 0, 250, 250);
    }
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
    for(int i = 0; i < BOARD_LEN; i++) {
        for(int j = 0; j < BOARD_LEN - i; j++) {
            unsigned int x_pos = x_orig + x_mov * i - x_mov * j;
            unsigned int y_pos = y_orig + y_mov * i + y_mov * j;
            draw_cube(x_pos, y_pos, i, j);
        }
    }
}

void Board::set_screen_size(int in_w, int in_h) {
    screen_width = in_w;
    screen_height = in_h;
    x_orig = screen_width/2;
    y_orig = screen_height/6 + get_orig_to_on_top();
    SQUARE_WIDTH = screen_width/19;
    x_mov = (unsigned int)(SQUARE_WIDTH * cos(2.0/6 * M_PI * 3 + 7*M_PI/6));
    y_mov = (unsigned int)(SQUARE_WIDTH*HEIGHT_DILATION * (sin(2.0/6 * M_PI * 4 + 7*M_PI/6) + sin(2.0/6 * M_PI * 3 + 7*M_PI/6)));
}

//  returns if a row and column is in the board 
bool Board::in_board(int r, int c) {
    return  r >= 0 &&
            c >= 0 &&
            r + c < BOARD_LEN;
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

int Board::get_board_len() {    return BOARD_LEN;   }
int Board::get_x_orig() {   return x_orig;  }
int Board::get_y_orig() {   return y_orig;  }
int Board::get_orig_to_on_top() {   return (int)(SQUARE_WIDTH * HEIGHT_DILATION + 10);  }
int Board::get_x_mov() {    return x_mov;   }
int Board::get_y_mov() {    return y_mov;   }

//  Returns the pixel coordinate of a cube
//  Remember to handle memory after calling
int* Board::get_cube_location(int row, int col) {
    int* pos = new int[2];
    pos[0] = x_orig + x_mov * row - x_mov * col;
    pos[1] = y_orig + y_mov * row + y_mov * col - get_orig_to_on_top();
    return pos;
}