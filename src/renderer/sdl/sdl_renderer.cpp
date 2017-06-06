//
// Created by robin on 5/10/17.
//

#include <iostream>
#include "settings.h"
#include "world/world.h"
#include "camera/camera_manager.h"
#include "sdl_renderer.h"

SDLRenderer::SDLRenderer(SDL_Renderer *engine, vec2 window_size) : Renderer<SDL_Renderer>(engine) {
    _window_size = window_size;
    init_textures();
}

SDLRenderer::~SDLRenderer() {
    SDL_DestroyRenderer(engine);
    SDL_DestroyTexture(_back_buffer_final);
    SDL_DestroyTexture(_back_buffer_world);
    SDL_DestroyTexture(_back_buffer_ui);
}

void SDLRenderer::draw_to_buffer(SDL_Texture *t, SDL_Rect *r) {
    draw_to_buffer(SDL_GetRenderTarget(engine), t, r);
}

void SDLRenderer::draw_to_buffer(SDL_Texture *buffer, SDL_Texture *t, SDL_Rect *r) {
    SDL_SetRenderTarget(engine, buffer);
    if(SDL_RenderCopy(engine, t, NULL, r) < 0) {
        std::cerr << SDL_GetError() << std::endl;
    }
}

SDL_Texture *SDLRenderer::get_ui_buffer() {
    return _back_buffer_ui;
}

SDL_Texture *SDLRenderer::get_world_buffer() {
    return _back_buffer_world;
}

SDL_Texture *SDLRenderer::create_texture(int width, int height, SDL_TextureAccess access) {
    SDL_Texture *tmp = SDL_CreateTexture(engine, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if(!tmp) {
        std::cerr << SDL_GetError() << std::endl;
    }
    return tmp;
}

void SDLRenderer::clear() {
    SDL_SetRenderTarget(engine, _back_buffer_final);
    SDL_SetRenderDrawColor(engine, 0, 0, 0, 0);
    SDL_RenderClear(engine);
    SDL_SetRenderTarget(engine, _back_buffer_ui);
    SDL_SetRenderDrawColor(engine, 0, 0, 0, 0);
    SDL_RenderClear(engine);
    SDL_SetRenderTarget(engine, _back_buffer_world);
    SDL_SetRenderDrawColor(engine, 0, 0, 0, 0);
    SDL_RenderClear(engine);
}

void SDLRenderer::show() {
    SDL_SetRenderTarget(engine, _back_buffer_final);
    SDL_RenderCopy(engine, _back_buffer_world, NULL, NULL);
    SDL_RenderCopy(engine, _back_buffer_ui, NULL, NULL);

    SDL_SetRenderTarget(engine, NULL);
    SDL_RenderCopy(engine, _back_buffer_final, NULL, NULL);
    SDL_RenderPresent(engine);
}

void SDLRenderer::set_render_target(SDL_Texture *t) {
    SDL_SetRenderTarget(engine, t);
}

void SDLRenderer::resize(const vec2 &v) {
    if(v.x != _window_size.x || v.y != _window_size.y) {
        _window_size.x = v.x;
        _window_size.y = v.y;
        window_size = _window_size;
        SDL_RenderSetLogicalSize(engine, (int) _window_size.x, (int) _window_size.y);
        SDL_Rect new_window_rect = {0, 0, (int) _window_size.x, (int) _window_size.y};
        SDL_RenderSetViewport(engine, &new_window_rect);
        CameraManager::get_instance()->resize(_window_size);
        SDL_DestroyTexture(_back_buffer_final);
        SDL_DestroyTexture(_back_buffer_world);
        SDL_DestroyTexture(_back_buffer_ui);
        init_textures();
    }
}

void SDLRenderer::init_textures() {
    _back_buffer_final = create_texture((int) _window_size.x, (int) _window_size.y);
    _back_buffer_ui = create_texture((int) _window_size.x, (int) _window_size.y);
    _back_buffer_world = create_texture((int) _window_size.x, (int) _window_size.y);
    SDL_SetTextureBlendMode(_back_buffer_world, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(_back_buffer_ui, SDL_BLENDMODE_BLEND);
}
