#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "board.h"
#include "creature.h"
using namespace std;

class Player : public Creature {
    public:
        Player(Board*);

        void spawn();
        void move();

        
};

#endif