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
        void spawn() override;
        void jump() override;


        void move();
};

#endif