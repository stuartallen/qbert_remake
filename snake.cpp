#include "snake.h"

Snake::Snake(Board* in_board, SpriteSheet* in_sprites) {
    JUMP_TIME = 700;
    ball = new Ball(in_board, in_sprites);
    board = in_board;
    sprites = in_sprites;
    snake_mode = false;
}

Snake::~Snake() {
    delete ball;
}

void Snake::spawn() {}

void Snake::set_jump_sound(Sound* in_s) {
    Creature::set_jump_sound(in_s);
    ball->set_jump_sound(in_s);
}

void Snake::set_player(Player* in_p) {
    player = in_p;
}

void Snake::animate() {
    if(!snake_mode) {
        snake_mode = check_if_bottom();
        row = ball->get_row();
        col = ball->get_col();
        if(!snake_mode) {
            ball->animate();
        } else {
            timer_start = SDL_GetTicks();
            old_row = row;
            old_col = col;
        }
    } else {
        if(transition_timer_done()) {
            Creature::animate();
            float cur_dist = player_dist();
            if(player_dist(row + 1, col) < cur_dist) {  move(1,0);  }
            else if(player_dist(row, col + 1) < cur_dist) {  move(0,1);  }
            else if(player_dist(row - 1, col) < cur_dist) {  move(-1,0);  }
            else {  move(0,-1);  }
        } else {
            //  stays still
            SDL_Rect rect;
            rect.x = ball->get_x_pos();
            rect.y = ball->get_y_pos();
            rect.w = 100;
            rect.h = 100;
            ball->get_sprites()->draw(&rect);
        }
    }
}

bool Snake::transition_timer_done() {
    return (SDL_GetTicks() - timer_start) >= WAIT_TIME;
}

float Snake::player_dist() {
    return pow(pow(row - player->get_old_row(), 2) + pow(col - player->get_old_col(), 2), 0.5);
}

float Snake::player_dist(int r, int c) {
    return pow(pow(r - player->get_old_row(), 2) + pow(c - player->get_old_col(), 2), 0.5);
}

bool Snake::check_if_bottom() {
    return (row + col) == board->get_board_len();
}