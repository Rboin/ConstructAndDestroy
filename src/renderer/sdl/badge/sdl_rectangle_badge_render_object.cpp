//
// Created by Stephan Schrijver on 1-6-2017.
//

#include "sdl_rectangle_badge_render_object.h"
#include "sdl/sdl_renderer.h"


SDL_RectangleBadgeRenderObject::SDL_RectangleBadgeRenderObject(const vec2 &position, const vec2 &size, sdl_data *color,
                                                               int radius) : SDL_BadgeRenderObject(position, size,
                                                                                                   color, radius) {

}

void SDL_RectangleBadgeRenderObject::render(SDLRenderer *renderer, const mat2 & transformation) {
    SDL_SetRenderDrawColor(renderer->get_engine(), this->get_data()->red, this->get_data()->green,
                           this->get_data()->blue, this->get_data()->alpha);
    for (int w = 0; w < _radius * 2; w++) {
        for (int h = 0; h < _radius * 2; h++) {
            int dx = _radius - w; // horizontal offset
            int dy = _radius - h; // vertical offset
            //if ((dx * dx + dy * dy) <= (_radius * _radius)) {
                SDL_RenderDrawPoint(renderer->get_engine(), _center.x + dx, _center.y + dy);
            //}

        }
    }
}