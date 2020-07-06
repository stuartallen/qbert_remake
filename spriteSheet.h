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

        //  used if sprite has direction
        bool has_dir;
        int cur_dir = 0;
        int** offsets;

        void next_sprite();
    public:
        const static int BL = 0;
        const static int BR = 1;
        const static int TL = 2;
        const static int TR = 3;

        //  Default constructor only here so can be assigned dynamically
        SpriteSheet();
        SpriteSheet(char const *path, SDL_Renderer* renderer);
        void set_up(char const *path, 
                    SDL_Renderer* renderer,
                    int x,
                    int y,
                    int w,
                    int h,
                    int max_sprite,
                    int c_ticks,
                    bool directional);
        ~SpriteSheet();
        void draw(SDL_Rect *position);

        void set_offsets(   int bl_x, int bl_y,
                            int br_x, int br_y,
                            int tl_x, int tl_y,
                            int tr_x, int tr_y);

        void set_dir(int);
        //void operator=(const SpriteSheet&);
};

#endif 