#include "game.h"

Game::Game() {  return; }

Game::Game(SDL_Renderer* in_r) {
    renderer = in_r;
    sprites = new SpriteSheet[3];

    set_up_sprites();

    
}

void Game::set_up_sprites() {
    //  Set up Qbert
    sprites[QBERT_SPRITE_ID].set_up(SPRITE_SHEET, 
                                    renderer, 
                                    QBERT_X_SPRITE_POS,
                                    QBERT_Y_SPRITE_POS,
                                    QBERT_SPRITE_WIDTH,
                                    QBERT_SPRITE_HEIGHT,
                                    QBERT_SPRITE_FRAMES,
                                    SPRITE_SWITCH_TIME,
                                    true);
    sprites[QBERT_SPRITE_ID].set_offsets(   QBERT_X_SPRITE_POS, QBERT_Y_SPRITE_POS,
                                            QBERT_X_SPRITE_POS + (QBERT_SPRITE_FRAMES + 1) * QBERT_SPRITE_WIDTH, QBERT_SPRITE_HEIGHT,
                                            QBERT_X_SPRITE_POS, QBERT_SPRITE_HEIGHT,
                                            QBERT_X_SPRITE_POS + (QBERT_SPRITE_FRAMES + 1) * QBERT_SPRITE_WIDTH, QBERT_SPRITE_HEIGHT);
}