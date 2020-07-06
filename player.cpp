#include <iostream>
#include "player.h"
using namespace std;

Player::Player(Board* in_board, SpriteSheet* in_sprites) {
    row = 0;
    col = 0;
    board = in_board;
    sprites = in_sprites;
}

void Player::spawn() {
    row = 0;
    col = 0;
}

void Player::jump() {
    Creature::jump();
    if(!jumping) {  board->update_color(row, col);  }
}