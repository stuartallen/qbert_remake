#include <iostream>
#include "player.h"
using namespace std;

Player::Player(Board* in_board) {
    row = 4;
    col = 2;
    board = in_board;
}

void Player::spawn() {
    row = 0;
    col = 0;
}

void Player::move(int d_row, int d_col) {
    row += d_row;
    col += d_col;
}

void Player::animate() {
    unsigned int x_pos = board->get_x_orig() + board->get_x_mov() * row - board->get_x_mov() * col;
    unsigned int y_pos = board->get_y_orig() + board->get_y_mov() * row + board->get_y_mov() * col - board->get_orig_to_on_top();
    filledCircleRGBA(   renderer, 
                        x_pos, 
                        y_pos, 
                        20,
                        255, 120, 0, 255);
}