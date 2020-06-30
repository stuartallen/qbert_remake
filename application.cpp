//  including iostream causes
//  memory allocation which is
//  stupid but it works
#include <iostream>
#include <time.h>
#include <string.h>
#include "board.h"
#include "sound.h"
#include "creature.h"
#include "player.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL2_gfxPrimitives.h>

#ifdef WIN32
// don't interfere with std::min,max
#define NOMINMAX
// https://seabird.handmade.network/blogs/p/2460-be_aware_of_high_dpi
#pragma comment(lib, "Shcore.lib")
// helpers for high DPI window scaling
#include <ShellScalingAPI.h>
#include <comdef.h>
#include <windows.h>
#endif

#define MUS_PATH "jump-9.wav"

using namespace std;

//  Functions with SDL
SDL_Window* set_up_window(int&,int&);
SDL_Renderer* set_up_renderer(SDL_Window*);
void destroy_window_renderer(SDL_Window*, SDL_Renderer*);

//  My functions
Sound** setUpSounds();
void guiMainLoop(Board&, Player&, Sound**);
void keyEvent(Player&, bool&, SDL_Event&, Sound**);

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

    //  Initialize sounds
    Sound** sounds = setUpSounds();

    Board board;
    Player player(&board);
    guiMainLoop(board, player, sounds);
    return 0;
}

//  does animating for game
void guiMainLoop(Board& board, Player& player, Sound** sounds)  {
    int screen_width, screen_height;
    SDL_Window* window = set_up_window(screen_width, screen_height);
    SDL_Renderer* renderer = set_up_renderer(window);
    board.set_renderer(renderer);
    board.set_screen_size(screen_width, screen_height);
    player.set_renderer(renderer);
    bool got_quit_event = false;
    while (!got_quit_event) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            keyEvent(player, got_quit_event, event, sounds);
        }

        // draw background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // draw foreground & player
        board.animate();
        player.animate();

        // present to screen
        SDL_RenderPresent(renderer);
    }
    destroy_window_renderer(window, renderer);
}

//  Handles the events when a key is pressed
void keyEvent(Player& player, bool& got_quit_event, SDL_Event& event, Sound** sounds) {
    switch (event.type) {
        case SDL_QUIT:
            got_quit_event = true;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
                got_quit_event = true;
                break;
            case SDLK_w:
                player.move(0,-1);
                sounds[0]->play();
                break;
            case SDLK_a:
                player.move(-1,0);
                sounds[0]->play();
                break;
            case SDLK_s:
                player.move(0,1);
                sounds[0]->play();
                break;
            case SDLK_d:
                player.move(1,0);
                sounds[0]->play();
                break;
            }
            break;
    }
}

//  Sets up all the sounds for the entire game
//  TODO Make the sounds initialized here
Sound** setUpSounds() {
    Sound** sounds = new Sound*[1];
    sounds[0] = new Sound(MUS_PATH);
    return sounds;
}

//  creates window object for the game
SDL_Window* set_up_window(int &screen_width, int &screen_height) {
#ifdef WIN32
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
#endif
    // NOTE: doing debug in fullscreen sucks.  The fullscreen window seems to prevent GUI of Visual Studio to work.
    // So, explicitly change this when you want to go fullscreen
    bool fullscreen = false; // FIXME - add this as a commandline option?
    if(fullscreen) {
        // get w/h after creating fullscreen window
        screen_width = 0;
        screen_height = 0;
    }
    else {
        // in high-dpi display, this will not give you a fullscreen window, but a scaled-down window size
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        screen_width = DM.w;
        screen_height = DM.h;
    }
    SDL_Window *window = SDL_CreateWindow("Qbert Screen",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      screen_width, screen_height,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    if (window == nullptr) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
    }
    if (fullscreen) {
        // for fullscreen find out after the window is created how big it really is
        SDL_GetWindowSize(window, &screen_width, &screen_height);
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