#include "sound.h"

//  Loads a Mix_chunk pointer
Sound::Sound(const char* noise_name) {
    noise_p = NULL;
    noise_p = Mix_LoadWAV(noise_name);
    if(noise_p == NULL) {
        std::cerr << "Failed to load sound" << std::endl;
    }
}

Sound::~Sound() {
    Mix_FreeChunk(noise_p);
    noise_p = NULL;
}

//plays the sound once
void Sound::play() {
    // channel, Mix_chunk*, repititions
    // channel -1 means the nearest available channel
    // It's not like stereo
    Mix_PlayChannel(-1, noise_p, 0);
}