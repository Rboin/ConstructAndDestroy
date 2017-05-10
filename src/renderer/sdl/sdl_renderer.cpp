//
// Created by robin on 5/10/17.
//

#include <iostream>
#include "sdl_renderer.h"

SDLRenderer::SDLRenderer(SDL_Renderer *engine) : Renderer<SDL_Renderer>(engine) {
    int width, height;
    SDL_GetRendererOutputSize(engine, &width, &height);
    _back_buffer = create_texture(width, height, SDL_TEXTUREACCESS_TARGET);
    SDL_SetRenderDrawBlendMode(engine, SDL_BLENDMODE_BLEND);
}

void SDLRenderer::draw_to_back_buffer(SDL_Texture *t, SDL_Rect *r) {
    SDL_SetRenderTarget(engine, _back_buffer);
    SDL_SetTextureBlendMode(_back_buffer, SDL_BLENDMODE_BLEND);
    if (SDL_RenderCopy(engine, t, NULL, r) < 0) {
        std::cerr << SDL_GetError() << std::endl;
    }
    SDL_SetRenderTarget(engine, NULL);
}

SDL_Texture *SDLRenderer::create_texture(int width, int height, SDL_TextureAccess access) {
    SDL_Texture *tmp = SDL_CreateTexture(engine, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if(!tmp) {
        std::cerr << SDL_GetError() << std::endl;
    }
    return tmp;
}

void SDLRenderer::clear() {
    SDL_RenderClear(engine);
}

void SDLRenderer::show() {
    SDL_SetRenderTarget(engine, NULL);
    SDL_RenderCopy(engine, _back_buffer, NULL, NULL);
    SDL_RenderPresent(engine);
}