#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class Sound {
        private:
                Mix_Chunk* noise_p;
        public:
                Sound();
                Sound(const char*);
                void operator=(const Sound&);
                ~Sound();

                void play();
};

#endif