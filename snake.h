#ifndef SNAKE_H
#define SNAKE_H

#include <cmath>
#include "creature.h"
#include "ball.h"
#include "player.h"

class Snake : public Creature {
    private:
        const int WAIT_TIME = 5000;
        int timer_start;

        Player* player;

        bool snake_mode;
        Ball* ball = nullptr;
    public:
        Snake(Board*, SpriteSheet*);
        ~Snake();

        void spawn() override;

        void set_player(Player*);
        void set_jump_sound(Sound*);
        void animate();
        bool transition_timer_done();
        float player_dist();
        float player_dist(int, int);

        bool check_if_bottom();
};

#endif