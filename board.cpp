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

//  draw one trapezoid
void Board::draw_cube(unsigned int x, unsigned int y) {
    Sint16** points = new Sint16*[7];
    for(int i = 0; i < 6; i++) {
        points[i] = new Sint16[2];
        points[i][0] = SQUARE_WIDTH * cos(2.0/6 * M_PI * i) + x;
        points[i][1] = SQUARE_WIDTH * sin(2.0/6 * M_PI * i) + y;
    }
    points[6] = new Sint16[2];
    points[6][0] = x;
    points[6][1] = y;
    cout << endl;
    for(int i = 0; i < 7; i++) {
        cout << points[i][0] << "\t" << points[i][1] << endl;
    }

    //  Top
    /*
    Sint16 points_x_top[] = {points[0][0], points[1][0], points[2][0], points[3][0], points[4][0], points[5][0], points[6][0]};
    
    Sint16 points_y_top[] = {points[0][1], points[1][1], points[2][1], points[3][1], points[4][1], points[5][1], points[6][1]};
    */
    
    Sint16 points_x_top[] = {   (Sint16) x, 
                                (Sint16) (x - SQUARE_WIDTH/2), 
                                (Sint16) x, 
                                (Sint16) (x + SQUARE_WIDTH/2)};
    Sint16 points_y_top[] = {   (Sint16) (y + SQUARE_WIDTH/HEIGHT_DILATION), 
                                (Sint16) y, 
                                (Sint16) (y - SQUARE_WIDTH/HEIGHT_DILATION), 
                                (Sint16) y};
                                
    // args are: renderer, x coords, y coords, point #, and rgba
    filledPolygonRGBA(renderer, points_x_top, points_y_top, 4, 250, 150, 0, 250);
    //  Bottom Left

    for(int i = 0; i < 7; i++) {
        delete [] points[i];
    }
    delete [] points;
}

//  draws all the platforms
void Board::animate() {
    SDL_RenderClear(renderer);
    unsigned int x_orig = SCREEN_WIDTH/2;
    unsigned int y_orig = SCREEN_HEIGHT/4;
    for(int i = 0; i < BOARD_LEN; i++) {
        for(int j = 0; j < BOARD_LEN - i; j++) {
            unsigned int x_pos = x_orig + SQUARE_WIDTH/2 * i - SQUARE_WIDTH/2 * j;
            unsigned int y_pos = y_orig + SQUARE_WIDTH * i + SQUARE_WIDTH * j;
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