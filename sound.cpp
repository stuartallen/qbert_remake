#include <iostream>
#include "sound.h"
using namespace std;

Sound::Sound(const char* sound_path) {
    /* Load the WAV */
	// the specs, length and buffer of our wav are filled
	if( SDL_LoadWAV(sound_path, &wav_spec, &wav_buffer, &wav_length) == NULL ){
	  cerr << "Audio file NULL" << endl;
	}
	// set the callback function
	wav_spec.callback = this->my_audio_callback;
	wav_spec.userdata = (void*) this;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length

    /* Open the audio device */
	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}
}

Sound::~Sound() {
    // shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);
}

void Sound::play_audio() {
    //TODO how to handle many consecutive calls
    audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length
	/* Start playing */
	SDL_PauseAudio(0);
}


// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
void Sound::my_audio_callback(void *userdata, Uint8 *stream, int len) {
	Sound* my_this = (Sound*) userdata;
	if (my_this->audio_len ==0) {
        cout << "here" << "\n";
        SDL_PauseAudio(1);
		return;
    }
	
    cout << my_this->audio_pos - my_this->wav_buffer << "\n";
	len = ( len > my_this->audio_len ? my_this->audio_len : len );
	SDL_memcpy (stream, my_this->audio_pos, len); 					// simply copy from one buffer into the other

	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another
	
	my_this->audio_pos += len;
	my_this->audio_len -= len;
    cout << my_this->audio_len << "\t" << len << "\n";
}