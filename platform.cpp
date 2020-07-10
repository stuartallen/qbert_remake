#include "platform.h"

//  Rows and cols are set as random lengths
Platform::Platform(Board* in_board, SpriteSheet* in_sprites) {
    board = in_board;
    sprites = in_sprites;
    if(rand() % 2) {
        row = rand() % board->get_board_len();
        col = -1;
    } else {
        col = rand() % board->get_board_len();
        row = -1;
    }
    int* loc = board->get_cube_location(row, col);
    x_pos = loc[0];
    y_pos = loc[1];
    delete [] loc;
}

Platform::~Platform() {
    //delete board;
}

void Platform::set_loc(int r, int c) {
    row = r;
    col = c;
    x_pos = board->get_cube_location(row, col)[0];
    y_pos = board->get_cube_location(row, col)[1];
}

void Platform::animate() {
    SDL_Rect rect;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = 100;
    rect.h = 100;
    sprites->draw(&rect);
}

void Platform::init_transport() {
    
}

void Platform::transport() {

}

int* Platform::get_pos() {
    int* pos = new int[2];
    pos[0] = x_pos;
    pos[1] = y_pos;
}