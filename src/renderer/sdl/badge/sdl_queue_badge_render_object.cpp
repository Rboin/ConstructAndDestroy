//
// Created by Stephan Schrijver on 1-6-2017.
//

#include "sdl_queue_badge_render_object.h"
#include "sdl/text/sdl_render_text_object.h"

SDL_QueueBadgeRenderObject::SDL_QueueBadgeRenderObject(const vec2 &position, const vec2 &size, TTF_Font *font,
                                                       sdl_data *color, int radius)
        : SDL_CircleBadgeRenderObject(position, size, color, radius) {

    vec2 text_size = {(float) _radius, (float) _radius};
    vec2 text_pos = _center - vec2(text_size.x / 2, text_size.y / 2);

    sdl_data textcolor = sdl_data(0, 0, 0, 255);
    _textdata = new sdl_text{textcolor.red, textcolor.green, textcolor.blue, std::to_string((int) _count).c_str(),
                             font};
    _text = new SDL_UI_RenderTextObject(text_pos, text_size, _textdata);
}

void SDL_QueueBadgeRenderObject::update_count(int count) {
    this->_count = count;
}

void SDL_QueueBadgeRenderObject::render(SDLRenderer *renderer,  const mat2 & transformations) {
    SDL_CircleBadgeRenderObject::render(renderer,transformations);

    _textdata->text = std::to_string((int)_count).c_str();
    _text->render(renderer, transformations);
}

SDL_QueueBadgeRenderObject::~SDL_QueueBadgeRenderObject() {
    clear_data();
}