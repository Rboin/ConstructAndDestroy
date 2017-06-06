//
// Created by Jeroen on 5/24/2017.
//

#include "sdl/text/sdl_render_text_object.h"
#include "sdl_badge_render_object.h"
#include "entity/base_entity.h"
#include "sdl/sdl_renderer.h"

SDL_BadgeRenderObject::SDL_BadgeRenderObject(const vec2 &position, const vec2 &size, sdl_data *color, int radius) : SDL_RenderObject(position, size, color) {
    _center = vec2{_position.x, _position.y};
    _radius = radius;
}

SDL_BadgeRenderObject::~SDL_BadgeRenderObject() {
    if(this->_text){
        delete this->_text;
    }
    clear_data();
}

void SDL_BadgeRenderObject::set_position(float x, float y) {
    _center =  vec2{_position.x, _position.y};
    RenderObject::set_position(x, y);
    vec2 text_center = {_position.x - (_size.x/2), _position.y - (_size.y/2)};
    _text->set_position(text_center.x, text_center.y);
}
