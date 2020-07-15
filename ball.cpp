#include "ball.h"

Ball::Ball(Board* in_board, SpriteSheet* in_sprites) {
    JUMP_TIME = 1000;
    board = in_board;
    sprites = in_sprites;
    spawned = false;
}

void Ball::spawn() {
    spawned = true;
    if(rand() % 2 == 0) {
        row = 0; col = 1;
    } else {
        row = 1; col = 0;
    }
    old_row = row;
    old_col = col;
    Creature::set_screen_pos();
}

void Ball::animate() {
    if(spawned) {
        Creature::animate();
        if(rand() % 2 == 0) {
            Creature::move(1,0);
        } else {
            Creature::move(0,1);
        }
    }
}

void Ball::jump() { Creature::jump();   }