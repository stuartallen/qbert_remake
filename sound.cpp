#include "sound.h"

//  Default constructor exists so a list can be made
Sound::Sound() {}

//  Loads a Mix_chunk pointer
Sound::Sound(const char* noise_name) {
    noise_p = NULL;
    noise_p = Mix_LoadWAV(noise_name);
    if(noise_p == NULL) {
        std::cerr << "Failed to load sound" << std::endl;
    }
}

//  Operator =
void Sound::operator=(const Sound& in_sound) {
    noise_p = in_sound.noise_p;
}

//  Sound destructor
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