#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "board.h"
#include "creature.h"
using namespace std;

class Player : public Creature {
    public:
        Player(Board*, SpriteSheet*);

        void spawn();
        void jump();
};

#endif