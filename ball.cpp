#include "ball.h"

Ball::Ball(Board* in_board, SpriteSheet* in_sprites) {
    board = in_board;
    sprites = in_sprites;
    spawn();
}

void Ball::spawn() {
    if(rand() % 2 == 0) {
        row = 0; col = 1;
    } else {
        row = 1; col = 0;
    }
    old_row = row;
    old_col = col;
}

void Ball::jump() {}