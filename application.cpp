//  including iostream causes
//  memory allocation which is
//  stupid but it works
#include <iostream>
#include <time.h>
#include "board.h"

#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

void guiMainLoop();

int main(int argc, char* argv[]) {
    guiMainLoop();

    return 0;
}

/*  creates screen  */
void guiMainLoop()  {
    int windowSizeX = 1200;
    int windowSizeY = 800;
    
    SDL_Window *window = SDL_CreateWindow("Qbert Screen",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      windowSizeX, windowSizeY,
                                      SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return;
    }

    /* Select the color for drawing. It is set to red here. */
    SDL_SetRenderDrawColor(renderer, 250, 150, 0, 255);

    /* Clear the entire screen to our selected color. */
    SDL_RenderClear(renderer);

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
                }
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}