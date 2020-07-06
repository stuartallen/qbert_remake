#include "spriteSheet.h"

/*
const int QBERT_SPRITE_HEIGHT = 48;
const int QBERT_SPRITE_WIDTH = 30;
const int QBERT_SPRITE_OFFSET_X = 76;
const int QBERT_SPRITE_OFFSET_Y = 0;
*/

SpriteSheet::SpriteSheet() {}

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

void SpriteSheet::set_up(   char const *path, 
                            SDL_Renderer* in_renderer,
                            int x,
                            int y,
                            int w,
                            int h,
                            int max_sprite,
                            int c_ticks,
                            bool directional) {
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
    m_clip.x = x;
    m_clip.y = y;
    m_clip.w = w;
    m_clip.h = h;
    MAX_SPRITE = max_sprite; 
    change_ticks = c_ticks;
    has_dir = directional;
    if(!directional) {
        offsets = new int*[1];
        offsets[0] = new int[2];
        offsets[0][0] = x;
        offsets[0][1] = y;
    }
}

SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture(m_spritesheet_image);
    if(has_dir) {
        for(int i = 0; i < 4; i++) {
            delete [] offsets[i];
        }
        delete [] offsets;
    } else {
        delete [] offsets[0];
        delete [] offsets;
    }
}

void SpriteSheet::next_sprite()    {
    cur_ticks = SDL_GetTicks();
    if(cur_ticks - last_ticks >= change_ticks) {
        last_ticks = SDL_GetTicks();
        if(cur_sprite < MAX_SPRITE - 1) {
            cur_sprite++;
        } else {
            m_clip.x -= (MAX_SPRITE - 1) * m_clip.w;
            cur_sprite = 0;
        }
        m_clip.x = offsets[cur_dir][0] + m_clip.w * cur_sprite;
        m_clip.y = offsets[cur_dir][1];
    }
}

//  Bases position off center of input rectangle    
void SpriteSheet::draw(SDL_Rect *render_rect)  {
    next_sprite();
    render_rect->x -= (render_rect->w)/2;
    render_rect->y -= (render_rect->h)/2;
    SDL_RenderCopy(renderer, m_spritesheet_image, &m_clip, render_rect);
} 

void SpriteSheet::set_offsets( int bl_x, int bl_y,
                                int br_x, int br_y,
                                int tl_x, int tl_y,
                                int tr_x, int tr_y) {
    if(has_dir) {
        offsets = new int*[4];
        for(int i = 0; i < 4; i++) {
            offsets[i] = new int[2];
        }
        offsets[BL][0] = bl_x; offsets[BL][1] = bl_y;
        offsets[BR][0] = br_x; offsets[BR][1] = br_y;
        offsets[TL][0] = tl_x; offsets[TL][1] = tl_y;
        offsets[TR][0] = tr_x; offsets[TR][1] = tr_y;
    }
}

void SpriteSheet::set_dir(int in_dir) {
    cur_dir = in_dir;
}

/*
void SpriteSheet::operator=(const SpriteSheet& in_sprite) {
    renderer = in_sprite.renderer;
    m_spritesheet_image = in_sprite.m_spritesheet_image;
    m_clip = in_sprite.m_clip;
    MAX_SPRITE = in_sprite.MAX_SPRITE;
    if(in_sprite.has_dir) {
        cur_dir = in_sprite.dir;
    }
}
*/