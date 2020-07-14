#include <iostream>
#include "player.h"
using namespace std;

Player::Player(Board* in_board, SpriteSheet* in_sprites) {
    alive = true;
    JUMP_TIME = 500;
    row = 0;
    col = 0;
    board = in_board;
    sprites = in_sprites;
}

void Player::set_coll_sound(Sound* in_s) {
    coll_sound = in_s;
}

void Player::set_fall_sound(Sound* in_s) {
    fall_sound = in_s;
}

void Player::set_enemies(Creature** in_enemies, int in_num_enemies) {
    enemies = in_enemies;
    num_enemies = in_num_enemies;
}

void Player::set_platforms(Platform* in_platforms, int num_plats) {
    platforms = in_platforms;
    num_platforms = num_plats;
}

void Player::spawn() {
    row = 0;
    col = 0;
}

void Player::jump() {
    Creature::jump();
    if(!jumping && Creature::on_board()) {  board->update_color(row, col);  }
}

void Player::animate() {
    if(!on_board()) {   
        Creature::animate();
        if(alive) {
            if(!transporting) {
                for(int i = 0; i < num_platforms; i++) {
                    if(row == platforms[i].get_row() && col == platforms[i].get_col()) {
                        transporting = true;
                        plat_id = i;
                        platforms[plat_id].start_moving();
                    }
                }
            }
            if(transporting) {
                int* loc = platforms[plat_id].get_pos();
                x_pos = loc[0];
                y_pos = loc[1];
            } else {
                fall_sound->play();
                alive = false;  
            }
        }
    }
    if(alive) {
        Creature::animate();
        for(int i = 0; i < num_enemies; i++) {
            if( enemies[i]->get_x_pos() <= x_pos && 
                enemies[i]->get_x_pos() + 50 >= x_pos &&
                enemies[i]->get_y_pos() <= y_pos &&
                enemies[i]->get_y_pos() + 50 >= y_pos) {
                alive = false;
                coll_sound->play();
            }
        }
    } else {    }
}