//
// Created by robin on 4/23/17.
//

#include "sdl_render_object.h"
#include "renderer.h"

SDL_RenderObject::SDL_RenderObject(const vec2 &position, const vec2 &size, sdl_data *data)
        : RenderObject(position, size, data) {
}

SDL_Texture *SDL_RenderObject::render(Renderer<SDL_Renderer> *renderer) {
    if (!_result) {
        init_texture(renderer);
    }

    SDL_SetRenderTarget(renderer->get_engine(), _result);
    SDL_Rect rect = {
            (int) _position.x, (int) _position.y, (int) _size.x, (int) _size.y
    };
    clear_texture(renderer, &rect);

    SDL_SetRenderDrawColor(renderer->get_engine(), _data->red, _data->green, _data->blue, 255);

    SDL_RenderFillRect(renderer->get_engine(), &rect);
    SDL_SetRenderDrawColor(renderer->get_engine(), 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer->get_engine(), (int) _position.x, (int) _position.y, (int) (_position.x + _size.x),
                       (int) (_position.y + _size.y));
    SDL_RenderDrawLine(renderer->get_engine(), (int) (_position.x + _size.x), (int) _position.y, (int) _position.x,
                       (int) (_position.y + _size.y));

    return _result;
}

void SDL_RenderObject::init_texture(Renderer<SDL_Renderer> *renderer) {
    _result = SDL_CreateTexture(renderer->get_engine(),
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                (int) _size.x,
                                (int) _size.y);
    SDL_SetTextureBlendMode(_result, SDL_BLENDMODE_BLEND);
}

void SDL_RenderObject::clear_texture(Renderer<SDL_Renderer> *renderer, SDL_Rect *rect) {
    SDL_SetRenderDrawColor(renderer->get_engine(), 0, 0, 0, 255);
    SDL_RenderFillRect(renderer->get_engine(), rect);
}

void SDL_RenderObject::clear_data() {
    SDL_DestroyTexture(_result);
}
