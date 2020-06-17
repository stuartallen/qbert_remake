#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <SDL.h>

class Sound {
    private:
        Uint8 *audio_pos; // pointer to the audio buffer to be played
        Uint32 audio_len; // remaining length of the sample we have to play
        
        Uint32 wav_length; // length of our sample
        Uint8 *wav_buffer; // buffer containing our audio file
        SDL_AudioSpec wav_spec; // the specs of our piece of music
	public:
        Sound(const char*);
        ~Sound();

        void play_audio();

        static void my_audio_callback(void*, Uint8*, int);
};

#endif