#include "snake.h"

Snake::Snake(Board* in_board, SpriteSheet* in_sprites) {
    row = -1;
    col = -1;
    JUMP_TIME = 700;
    ball = new Ball(in_board, in_sprites);
    ball->set_renderer(renderer);
    board = in_board;
    sprites = in_sprites;
    snake_mode = false;
    spawned = false;
}

Snake::~Snake() {
    delete ball;
}

void Snake::spawn() {
    ball->spawn();
    old_row = 0;
    old_col = 0;
    row = 0;
    col = 0;

    spawned = true;
    snake_mode = false;
}

void Snake::set_jump_sound(Sound* in_s) {
    Creature::set_jump_sound(in_s);
    ball->set_jump_sound(in_s);
}

void Snake::set_snake_sprite(SpriteSheet* in_s) {
    sprites = in_s;
}

void Snake::set_player(Player* in_p) {
    player = in_p;
}

void Snake::animate() {
    if(spawned) {
        if(!snake_mode) {
            snake_mode = check_if_bottom();
            if(!snake_mode) {
                ball->animate();
            } else {
                timer_start = SDL_GetTicks();
            }
        } else {
            if(transition_timer_done()) {
                Creature::animate();
                //  Move the ball off the board
                ball->move(-10,-10);
                ball->set_screen_pos();
                float cur_dist = player_dist();
                int min_dir = 0;
                float dists[4] = {player_dist(row + 1, col),
                                player_dist(row, col + 1),
                                player_dist(row - 1, col),
                                player_dist(row, col - 1)};
                for(int i = 1; i < 4; i++) {
                    if(dists[i] <= dists[min_dir]) { min_dir = i;   }
                }
                if(min_dir == 0) {  move(1,0); }
                else if(min_dir == 1) { move(0,1); }
                else if(min_dir == 2) { move(-1,0);  }
                else {  move(0,-1);  }
            } else {
                cout << old_row << row << old_col << col << endl;
                row = ball->get_old_row();
                col = ball->get_old_col();
                old_row = row;
                old_col = col;
                Creature::set_screen_pos();
                SDL_Rect rect;
                rect.x = ball->get_x_pos();
                rect.y = ball->get_y_pos();
                rect.w = 100;
                rect.h = 100;
                ball->get_sprites()->draw(&rect);
            }
        }
    }
}

bool Snake::transition_timer_done() {
    int cur_time = SDL_GetTicks();
    return (cur_time - timer_start) >= WAIT_TIME;
}

float Snake::player_dist() {
    return pow(pow((float) (row - player->get_old_row()), 2) + pow((float) (col - player->get_old_col()), 2), 0.5);
}

float Snake::player_dist(int r, int c) {
    return pow(pow((float) (r - player->get_old_row()), 2) + pow((float) (c - player->get_old_col()), 2), 0.5);
}

bool Snake::check_if_bottom() {
    return (ball->get_old_row() + ball->get_old_col()) == board->get_board_len() - 1;
}

Ball* Snake::get_ball() {   return ball;    }