//
// Created by robin on 5/10/17.
//

#include <iostream>
#include "sdl_renderer.h"

SDLRenderer::SDLRenderer(SDL_Renderer *engine) : Renderer<SDL_Renderer>(engine) {
    int width, height;
    SDL_GetRendererOutputSize(engine, &width, &height);
    _back_buffer = create_texture(width, height);
    SDL_SetRenderDrawBlendMode(engine, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(engine, _back_buffer);
}

SDLRenderer::~SDLRenderer() {
    SDL_DestroyTexture(_back_buffer);
    SDL_DestroyRenderer(engine);
    clear();
}

void SDLRenderer::draw_to_back_buffer(SDL_Texture *t, SDL_Rect *r) {
    SDL_SetRenderTarget(engine, _back_buffer);
    if (SDL_RenderCopy(engine, t, NULL, r) < 0) {
        std::cerr << SDL_GetError() << std::endl;
    }
}

SDL_Texture *SDLRenderer::get_back_buffer() {
    return _back_buffer;
}

SDL_Texture *SDLRenderer::create_texture(int width, int height, SDL_TextureAccess access) {
    SDL_Texture *tmp = SDL_CreateTexture(engine, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if(!tmp) {
        std::cerr << SDL_GetError() << std::endl;
    }
    return tmp;
}

void SDLRenderer::clear () {
    SDL_SetRenderDrawColor(engine, 0, 0, 0, 255);
    SDL_RenderClear(engine);
}

void SDLRenderer::show () {
    SDL_SetRenderTarget(engine, NULL);
    SDL_RenderCopy(engine, _back_buffer, NULL, NULL);
    SDL_RenderPresent(engine);
    SDL_SetRenderTarget(engine, _back_buffer);
}
