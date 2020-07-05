#include "creature.h"

Creature::Creature() { 
    jump_x = 0;
    jump_y = 0;
    old_row = 0;
    row = 0;
    old_col = 0;
    col = 0;
    start_jump_time = 0;
    bez_pts = new int*[4];
    jumping = false;
    for(int i = 0; i < 4; i++) {
        bez_pts[i] = new int[2];
    }
    return; 
}

Creature::Creature(Board* in_board, SpriteSheet* in_sprites) {
    board = in_board;
    sprites = in_sprites;
}

Creature::~Creature() {
    for(int i = 0; i < 4; i++) {
        delete [] bez_pts[i];
    }
    delete [] bez_pts;
}

void Creature::animate() {
    set_screen_pos();
}

void Creature::set_screen_pos() {
    if(jumping) {   
        jump(); 
        x_pos = jump_x;
        y_pos = jump_y;
    } else {
        x_pos = board->get_x_orig() + board->get_x_mov() * old_row - board->get_x_mov() * old_col + jump_x;
        y_pos = board->get_y_orig() + board->get_y_mov() * old_row + board->get_y_mov() * old_col - board->get_orig_to_on_top() + jump_y;
    }
}

void Creature::move(int d_row, int d_col) {
    if(!jumping) {
        jump_sound->play();
        old_row = row;
        old_col = col;
        row += d_row;
        col += d_col;
        init_jump(d_row, d_col);
    }
}

//  Calibrates the jump animation
//  Assume jumping is true
void Creature::init_jump(int d_row, int d_col) {
    //  Set bezie points
    bez_pts[0][0] = x_pos;  bez_pts[0][1] = y_pos;
    int* last_point = board->get_cube_location(old_row + d_row, old_col + d_col);
    bez_pts[1][0] = 2 * x_pos/3 + last_point[0]/3;  bez_pts[1][1] = 2 * y_pos/3 + last_point[1]/3 - JUMP_HEIGHT;
    bez_pts[2][0] = x_pos/3 + 2 * last_point[0]/3;  bez_pts[2][1] = y_pos/3 + 2 * last_point[1]/3 - JUMP_HEIGHT;
    bez_pts[3][0] = last_point[0];  bez_pts[3][1] = last_point[1];

    jumping = true;
    delete [] last_point;
    start_jump_time = SDL_GetTicks();
}

//  Alters jump_x/y
//  Assume jumping is true
void Creature::jump() {
    float t = (float) (SDL_GetTicks() - start_jump_time) / JUMP_TIME;
    if(t < 1) {
        jump_x = pow((1-t),3) * bez_pts[0][0] + 3*pow((1-t),2) * t * bez_pts[1][0] + 3*(1-t)*pow(t,2) * bez_pts[2][0] + pow(t,3) * bez_pts[3][0];
		jump_y = pow((1-t),3) * bez_pts[0][1] + 3*pow((1-t),2) * t * bez_pts[1][1] + 3*(1-t)*pow(t,2) * bez_pts[2][1] + pow(t,3) * bez_pts[3][1];
    } else {
        old_row = row;
        old_col = col;
        jump_x = 0;
        jump_y = 0;
        jumping = false;
        start_jump_time = 0;
    }
}

void Creature::set_renderer(SDL_Renderer* in_renderer) {    renderer = in_renderer; }
void Creature::set_jump_sound(Sound* js) {  jump_sound = js;    }

int Creature::get_row() {   return row; }
int Creature::get_col() {   return col; }

int Creature::get_pos() {
    return 10 * row + col;
}

bool Creature::on_board() {
    return  row >= 0 &&
            col >= 0 &&
            row < board->get_board_len() - col;
}