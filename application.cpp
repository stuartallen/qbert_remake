//  including iostream causes
//  memory allocation which is
//  stupid but it works
#include <iostream>
#include <time.h>
#include <string.h>
#include "board.h"
#include "sound.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL2_gfxPrimitives.h>

#define MUS_PATH "jump-9.wav"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


using namespace std;

SDL_Window* set_up_window();
SDL_Renderer* set_up_renderer(SDL_Window*);
void destroy_window_renderer(SDL_Window*, SDL_Renderer*);
void guiMainLoop(Board&, Sound&);

int main(int argc, char* argv[]) {
    // Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
            cerr << "Could not initialize sdl" << endl;
			return 1;
    }
    /// Initialize Audio Mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )   {
        cerr << "Could not initialize mixer" << endl;
        return 1;
    }

    Sound jump(MUS_PATH);

    Board board;
    guiMainLoop(board, jump);
    return 0;
}

//  does animating for game
void guiMainLoop(Board& board, Sound& jump)  {
    SDL_Window* window = set_up_window();
    SDL_Renderer* renderer = set_up_renderer(window);
    board.set_renderer(renderer);
    board.set_screen_size(SCREEN_WIDTH, SCREEN_HEIGHT);

    bool got_quit_event = false;
    while (!got_quit_event) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                got_quit_event = true;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    got_quit_event = true;
                    break;
                case SDLK_SPACE:
                    jump.play();
                    break;
                }
                break;
            }
        }

        // draw background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // draw foreground & player
        board.animate();

        // present to screen
        SDL_RenderPresent(renderer);
    }
    destroy_window_renderer(window, renderer);
}

//  creates window object for the game
SDL_Window* set_up_window() {
    SDL_Window *window = SDL_CreateWindow("Qbert Screen",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SCREEN_WIDTH, SCREEN_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
    }
    return window;
}

//  creates renderer object for game    
SDL_Renderer* set_up_renderer(SDL_Window* window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
    }
    return renderer;
}

//  Handles the memory from renderer and window and quits SDL   
void destroy_window_renderer(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}