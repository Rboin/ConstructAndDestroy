//
// Created by Jeroen on 5/24/2017.
//

#include "sdl/text/sdl_render_text_object.h"
#include "sdl_badge_render_object.h"
#include "entity/base_entity.h"
#include "sdl/sdl_renderer.h"

SDL_BadgeRenderObject::SDL_BadgeRenderObject(const vec2 &position, const vec2 &size, TTF_Font *font, sdl_data *color, int radius) : SDL_RenderObject(position, size, color) {
    _center = vec2{_position.x, _position.y};
    _radius = radius;

    sdl_data textcolor = sdl_data(0, 0, 0, 255);
    vec2 text_size = {(float)_radius, (float)_radius};
    vec2 text_pos = _center - vec2(text_size.x / 2, text_size.y / 2);
    _textdata = new sdl_text{textcolor.red, textcolor.green, textcolor.blue, std::to_string((int)_count).c_str(), font};
    _text = new SDL_UI_RenderTextObject(text_pos, text_size, _textdata);
}

void SDL_BadgeRenderObject::render(SDLRenderer *renderer) {
    SDL_SetRenderDrawColor(renderer->get_engine(), this->get_data()->red, this->get_data()->green, this->get_data()->blue, this->get_data()->alpha);
    for (int w = 0; w < _radius * 2; w++) {
        for (int h = 0; h < _radius * 2; h++) {
            int dx = _radius - w; // horizontal offset
            int dy = _radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (_radius * _radius)) {
                SDL_RenderDrawPoint(renderer->get_engine(), _center.x + dx, _center.y + dy);
            }
        }
    }

    _textdata->text = std::to_string((int)_count).c_str();
    _text->render(renderer);
}

void SDL_BadgeRenderObject::update_count(int count) {
    this->_count = count;
}


SDL_BadgeRenderObject::~SDL_BadgeRenderObject() {
    if(this->_text){
        delete this->_text;
    }
    clear_data();
}
