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

void Player::animate() {
    set_screen_pos();
    SDL_Rect rect;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = 100;
    rect.h = 100;
    sprites->draw_qbert(&rect);
}

void Player::jump() {
    Creature::jump();
    if(!jumping) {  board->update_color(row, col);  }
}