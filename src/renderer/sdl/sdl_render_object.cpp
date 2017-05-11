//
// Created by robin on 4/23/17.
//

#include "sdl_render_object.h"
#include "sdl/sdl_renderer.h"

SDL_RenderObject::SDL_RenderObject(const vec2 &position, const vec2 &size, sdl_data *data)
        : RenderObject(position, size, data) {
    rectangle = new SDL_Rect{
            (int) position.x, (int) position.y,
            (int) size.x, (int) size.y
    };
}

void SDL_RenderObject::render(SDLRenderer *renderer) {
    if (!_result) {
        init_texture(renderer);
    }
    SDL_SetRenderTarget(renderer->get_engine(), _result);
    SDL_SetRenderDrawColor(renderer->get_engine(), _data->red, _data->green, _data->blue, _data->alpha);
    SDL_RenderFillRect(renderer->get_engine(), rectangle);
    renderer->draw_to_back_buffer(_result, rectangle);

}

void SDL_RenderObject::init_texture(SDLRenderer *renderer) {
    if (_result) {
        SDL_DestroyTexture(_result);
        _result = nullptr;
    }
    _result = renderer->create_texture((int) _size.x, (int) _size.y);
}

void SDL_RenderObject::clear_texture(SDLRenderer *renderer, SDL_Rect *rect) {
    SDL_SetRenderDrawColor(renderer->get_engine(), 0, 0, 0, 255);
    SDL_RenderFillRect(renderer->get_engine(), rect);
}

void SDL_RenderObject::clear_data() {
    SDL_DestroyTexture(_result);
    _result = nullptr;
}