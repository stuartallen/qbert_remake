#include "spriteSheet.h"

const int QBERT_SPRITE_HEIGHT = 48;
const int QBERT_SPRITE_WIDTH = 30;
const int QBERT_SPRITE_OFFSET_X = 76;
const int QBERT_SPRITE_OFFSET_Y = 0;

SpriteSheet::SpriteSheet(char const *path, SDL_Renderer *renderer) {
    SDL_Surface* surface = NULL;
    surface = SDL_LoadBMP(path);
    if(surface != NULL) {
        m_clip.x = 0;
        m_clip.y = 0;
        m_clip.w = QBERT_SPRITE_WIDTH;
        m_clip.h = QBERT_SPRITE_HEIGHT;
        m_spritesheet_image = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    } else {
        cerr << "Sprite sheet is NULL\t" << SDL_GetError() << endl;
    }
}

SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture(m_spritesheet_image);
}

void SpriteSheet::select_qbert(int i)
{
    m_clip.x = QBERT_SPRITE_OFFSET_X + i * QBERT_SPRITE_WIDTH;
}

void SpriteSheet::draw_qbert(SDL_Renderer *renderer, SDL_Rect *render_rect, int i)
{
    select_qbert(i);
    SDL_RenderCopy(renderer, m_spritesheet_image, &m_clip, render_rect);
} 