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

void Player::move() {
    return;
}