#include <iostream>
#include "player.h"
using namespace std;

Player::Player(Board* in_board) {
    row = 0;
    col = 0;
    board = in_board;
}

void Player::spawn() {
    row = 0;
    col = 0;
}

void Player::animate() {
    set_screen_pos();
    filledCircleRGBA(   renderer, 
                        x_pos, 
                        y_pos, 
                        20,
                        255, 120, 0, 255);
    board->update_color(row, col);
}