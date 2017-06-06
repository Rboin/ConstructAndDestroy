//
// Created by Sander on 18-5-2017.
//

#include "sdl_progressbar_render_object.h"
#include "sdl/sdl_renderer.h"

SDL_ProgressbarRenderObject::SDL_ProgressbarRenderObject(const vec2 &position, const vec2 &size, SDL_Color color, sdl_data *data)
        : SDL_RenderObject(position, size, data) {
    _progress = 0.5;
    _color = color;
}

void SDL_ProgressbarRenderObject::render(SDLRenderer *renderer, const mat2 &transformations) {
    if (!_result) {
        init_texture(renderer);
    }

    renderer->draw_to_buffer(_result, &get_transformed_rectangle(transformations));

    draw(renderer);
}

void SDL_ProgressbarRenderObject::draw(SDLRenderer *renderer) {
    int x = (int)this->get_position()->x;
    int y = (int)this->get_position()->y;
    float progress_bar_width = this->get_size()->x;
    float progress_bar_height = this->get_size()->y;

    SDL_Rect background_rect = {x, y, (int)progress_bar_width, (int)progress_bar_height};
    SDL_SetRenderDrawColor(renderer->get_engine(), 0, 0, 0, 255);
    SDL_RenderFillRect(renderer->get_engine(), &background_rect);

    float pb_percentage = _progress * progress_bar_width;

    SDL_Rect progressbar_rect = {x, y, (int)pb_percentage, (int)progress_bar_height};
    SDL_SetRenderDrawColor(renderer->get_engine(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(renderer->get_engine(), &progressbar_rect);
}

void SDL_ProgressbarRenderObject::set_progress(float progress) {
    _progress = progress;
}

SDL_ProgressbarRenderObject::~SDL_ProgressbarRenderObject() {
    delete _data;
    clear_data();
}
