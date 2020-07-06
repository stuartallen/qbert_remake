#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "creature.h"
using namespace std;

class Ball : public Creature {
    private:
    public:
        void move();
        void spawn() override;
        void animate() override;
        void jump() override;
}