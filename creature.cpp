#include "creature.h"

Creature::Creature() {  return; }

Creature::Creature(Board* in_board) {
    board = in_board;
}

void Creature::animate() {
    set_screen_pos();
}

void Creature::set_screen_pos() {
    x_pos = board->get_x_orig() + board->get_x_mov() * row - board->get_x_mov() * col;
    y_pos = board->get_y_orig() + board->get_y_mov() * row + board->get_y_mov() * col - board->get_orig_to_on_top();
}

void Creature::move(int d_row, int d_col) {
    row += d_row;
    col += d_col;
}

void Creature::set_renderer(SDL_Renderer* in_renderer) {
    renderer = in_renderer;
}

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

