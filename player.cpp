#include <iostream>
#include "player.h"
using namespace std;

Player::Player(Board* in_board) {
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
    filledCircleRGBA(   renderer, 
                        board->get_x_orig(), 
                        board->get_y_orig(), 
                        20,
                        250, 150, 0, 250);
}