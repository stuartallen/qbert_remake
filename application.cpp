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

SDL_Window* set_up_window();
SDL_Renderer* set_up_renderer(SDL_Window*);
void destroy_window_renderer(SDL_Window*, SDL_Renderer*);
void guiMainLoop();

int main(int argc, char* argv[]) {
    guiMainLoop();

    return 0;
}

//  does animating for game
void guiMainLoop()  {
    SDL_Window* window = set_up_window();
    SDL_Renderer* renderer = set_up_renderer(window);

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

        SDL_RenderClear(renderer);

        SDL_Rect rect;
        rect.x = 250;
        rect.y = 150;
        rect.w = 200;
        rect.h = 200;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);

        /*  Draw background and update screen   */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }
    destroy_window_renderer(window, renderer);
}

//  creates window object for the game
SDL_Window* set_up_window() {
    const int windowSizeX = 1200;
    const int windowSizeY = 800;
    SDL_Window *window = SDL_CreateWindow("Qbert Screen",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      windowSizeX, windowSizeY,
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