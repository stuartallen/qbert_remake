//  including iostream causes
//  memory allocation which is
//  stupid but it works
#include <iostream>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "sound.h"
#include "creature.h"
#include "player.h"
#include "spriteSheet.h"
#include "ball.h"
#include "snake.h"
#include "platform.h"
#include "game.h"

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

#define QBERT_JUMP "jump-9.wav"
#define BALL_JUMP "jump-5.wav"
#define SNAKE_JUMP "jump-4.wav"
#define COLLIDE "explode-3.wav"
#define FALL_LOSE "lose-5.wav"

#define SPRITE_SHEET "QBert3Sheet1.bmp"

using namespace std;

//  Functions with SDL
SDL_Window* set_up_window(int&,int&);
SDL_Renderer* set_up_renderer(SDL_Window*);
void destroy_window_renderer(SDL_Window*, SDL_Renderer*);

//  My functions
void test_game();

Sound** setUpSounds();
void guiMainLoop(Board&, Sound**);
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

    //  Seed random
    srand( time(NULL));

    //  Initialize sounds
    //Sound** sounds = setUpSounds();

    //Board board;
    //guiMainLoop(board, sounds);
    test_game();
    return 0;
}

void test_game() {
    int screen_width, screen_height;
    SDL_Window* window = set_up_window(screen_width, screen_height);
    SDL_Renderer* renderer = set_up_renderer(window);

    //Game *game = new Game(renderer, screen_width, screen_height);
    Game game(renderer, screen_width, screen_height);
    while(game.going()) {
        game.loop();
    }
}

//  does animating for game
void guiMainLoop(Board& board, Sound** sounds)  {
    int screen_width, screen_height;
    SDL_Window* window = set_up_window(screen_width, screen_height);
    SDL_Renderer* renderer = set_up_renderer(window);

    
    board.set_renderer(renderer);
    board.set_screen_size(screen_width, screen_height);

    //  Set up sprites
    SpriteSheet* sprites = new SpriteSheet[3];
    // offset_x, offset_y, width, height, frames, time in frame
    sprites[0].set_up(SPRITE_SHEET, renderer, 76 + 30, 0, 30, 48, 3, 100, true);
    sprites[0].set_offsets( 76 + 30, 0,
                            76 + 4 * 30, 0,
                            76 + 30, 48,
                            76 + 4 * 30, 48);
    //  122 to 147, 173 to 198, 148 to 172
    //  98 to 130
    sprites[1].set_up(SPRITE_SHEET, renderer, 122, 98, 25, 32, 3, 200, false);
    sprites[2].set_up(SPRITE_SHEET, renderer, 193, 98, 30, 32, 3, 200, false);
    Player player(&board, &sprites[0]);
    player.set_renderer(renderer);
    player.set_jump_sound(sounds[0]);

    Ball red_ball(&board, &sprites[1]);
    red_ball.set_renderer(renderer);
    red_ball.set_jump_sound(sounds[1]);

    Snake snake(&board, &sprites[2]);
    snake.set_renderer(renderer);
    snake.set_jump_sound(sounds[4]);
    snake.set_player(&player);
    snake.set_snake_sprite(&sprites[1]);

    Creature** enemies = new Creature*[2];
    enemies[0] = &red_ball;
    enemies[1] = &snake;

    Platform platform(&board, &sprites[1]);

    player.set_enemies(enemies, 2);
    player.set_coll_sound(sounds[2]);
    player.set_fall_sound(sounds[3]);
    player.set_platforms(&platform, 1);

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
        if(player.get_old_row() >= 0 && player.get_old_col() >= 0) {
            board.animate();
            platform.animate();
            player.animate();
        } else {
            platform.animate();
            player.animate();
            board.animate();
        }
        snake.animate();
        red_ball.animate();

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
                player.set_sprite_dir(SpriteSheet::TR);
                player.move(0,-1);
                break;
            case SDLK_a:
                player.set_sprite_dir(SpriteSheet::TL);
                player.move(-1,0);
                break;
            case SDLK_s:
                player.set_sprite_dir(SpriteSheet::BL);
                player.move(0,1);
                break;
            case SDLK_d:
                player.set_sprite_dir(SpriteSheet::BR);
                player.move(1,0);
                break;
            }
            break;
    }
}

//  Sets up all the sounds for the entire game
//  TODO Make the sounds initialized here
Sound** setUpSounds() {
    Sound** sounds = new Sound*[5];
    sounds[0] = new Sound(QBERT_JUMP);
    sounds[1] = new Sound(BALL_JUMP);
    sounds[2] = new Sound(COLLIDE);
    sounds[3] = new Sound(FALL_LOSE);
    sounds[4] = new Sound(SNAKE_JUMP);
    return sounds;
}

//  creates window object for the game
SDL_Window* set_up_window(int &screen_width, int &screen_height) {
// FIXME - not sure what to do for High DPI Macintoshes 
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
                                      SDL_WINDOW_OPENGL | 
#ifdef WIN32
                                      SDL_WINDOW_ALLOW_HIGHDPI |
#endif
                                      (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
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