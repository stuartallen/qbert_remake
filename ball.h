#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <stdlib.h>
#include "creature.h"
using namespace std;

class Ball : public Creature {
    private:
    public:
        Ball(Board*, SpriteSheet*);
        ~Ball() override;
        void spawn() override;
        void jump() override;

        void animate(bool) override;

        void set_spawned_true();

        void set_off_screen();
};

#endif