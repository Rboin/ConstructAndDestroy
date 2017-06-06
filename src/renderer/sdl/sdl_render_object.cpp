//
// Created by robin on 4/23/17.
//

#include "sdl_render_object.h"
#include "sdl/sdl_renderer.h"
#include "matrix.h"

SDL_RenderObject::SDL_RenderObject(const vec2 &position, const vec2 &size, sdl_data *data)
        : RenderObject(position, size, data) {
    rectangle = {
        (int) position.x, (int) position.y,
        (int) size.x, (int) size.y
    };
}

SDL_RenderObject::~SDL_RenderObject() {
    delete _data;
    clear_data();
}

void SDL_RenderObject::render(SDLRenderer *renderer, const mat2 &transformations) {
    SDL_SetRenderDrawColor(renderer->get_engine(), _data->red, _data->green, _data->blue, _data->alpha);
    SDL_RenderFillRect(renderer->get_engine(), &get_transformed_rectangle(transformations));
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

SDL_Rect &SDL_RenderObject::get_transformed_rectangle(const mat2 &transformations) {
    for(unsigned int i = 0; i < sizeof(_points) / sizeof(vec2); i++) {
        point_buffer[i] = _points[i] * transformations;
    }
    rectangle = {
        (int) point_buffer[0].x, (int) point_buffer[0].y,
        (int) (point_buffer[1].x - point_buffer[0].x), (int) (point_buffer[3].y - point_buffer[0].y)
    };
    return rectangle;
}
