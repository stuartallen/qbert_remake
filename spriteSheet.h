#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <iostream>
#include <SDL.h>
using namespace std;

class SpriteSheet {
    private:
        //  renderer for sprite
        SDL_Renderer* renderer;
        //  texture image holding all the sprites
        SDL_Texture* m_spritesheet_image;
        // region to "clip" from the sprite sheet
        SDL_Rect     m_clip;

        int cur_ticks;
        int last_ticks;
        int change_ticks = 0;
        int cur_sprite = 0;
        int MAX_SPRITE;

        void next_sprite();
    public:
        //  Default constructor only here so can be assigned dynamically
        SpriteSheet(char const *path, SDL_Renderer* renderer);
        void set_up( int x,
                int y,
                int w,
                int h,
                int max_sprite,
                int c_ticks);
        ~SpriteSheet();
        void draw_qbert(SDL_Rect *position);
};

#endif 