#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <SDL.h>

class SpriteSheet
{
    void select_qbert(int i);
public:
    SpriteSheet(char const *path, SDL_Renderer *renderer);
    ~SpriteSheet();
    void draw_qbert(SDL_Renderer *renderer, SDL_Rect *position, int i);

private:
    //  texture image holding all the sprites
    SDL_Texture* m_spritesheet_image;
    // region to "clip" from the sprite sheet
    SDL_Rect     m_clip;
};

#endif