#include "spriteSheet.h"

/*
const int QBERT_SPRITE_HEIGHT = 48;
const int QBERT_SPRITE_WIDTH = 30;
const int QBERT_SPRITE_OFFSET_X = 76;
const int QBERT_SPRITE_OFFSET_Y = 0;
*/

SpriteSheet::SpriteSheet(   char const *path,
                            SDL_Renderer* in_renderer) {
    SDL_Surface* surface = NULL;
    surface = SDL_LoadBMP(path);
    if(surface != NULL) {
        renderer = in_renderer;
        cur_ticks = SDL_GetTicks();
        last_ticks = SDL_GetTicks();
        m_spritesheet_image = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    } else {
        cerr << "Sprite sheet is NULL\t" << SDL_GetError() << endl;
    }
}

void SpriteSheet::set_up(   int x,
                            int y,
                            int w,
                            int h,
                            int max_sprite,
                            int c_ticks) {
    m_clip.x = x;
    m_clip.y = y;
    m_clip.w = w;
    m_clip.h = h;
    MAX_SPRITE = max_sprite; 
    change_ticks = c_ticks;

    //m_clip.x -= m_clip.w;
}

SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture(m_spritesheet_image);
}

void SpriteSheet::next_sprite()    {
    cur_ticks = SDL_GetTicks();
    if(cur_ticks - last_ticks >= change_ticks) {
        last_ticks = SDL_GetTicks();
        cout << cur_sprite << "\t" << m_clip.x << endl;
        if(cur_sprite < MAX_SPRITE - 1) {
            m_clip.x += m_clip.w;
            cur_sprite++;
        } else {
            m_clip.x -= (MAX_SPRITE - 1) * m_clip.w;
            cur_sprite = 0;
        }
    }
}

//  Bases position off center of input rectangle    
void SpriteSheet::draw_qbert(SDL_Rect *render_rect)  {
    next_sprite();
    render_rect->x -= (render_rect->w)/2;
    render_rect->y -= (render_rect->h)/2;
    SDL_RenderCopy(renderer, m_spritesheet_image, &m_clip, render_rect);
} 