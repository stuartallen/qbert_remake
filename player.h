#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "sound.h"
#include "board.h"
#include "creature.h"
#include "platform.h"
using namespace std;

class Player : public Creature {
    private:
        Creature** enemies;
        int num_enemies = 0;
        Platform* platforms;
        int num_platforms;
        bool alive;

        bool transporting = false;
        //  represents the platform the player is traveling on
        int plat_id = -1;

        Sound* coll_sound = nullptr;
        Sound* fall_sound = nullptr;
    public:
        Player(Board*, SpriteSheet*);
        void set_coll_sound(Sound*);
        void set_fall_sound(Sound*);
        void set_enemies(Creature**, int);
        void set_platforms(Platform*, int);
        void spawn();
        void jump();
        void animate();
};

#endif