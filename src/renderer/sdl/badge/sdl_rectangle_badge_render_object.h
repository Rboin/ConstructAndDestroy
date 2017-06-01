//
// Created by Stephan Schrijver on 1-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RECTANGLE_BADGE_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_RECTANGLE_BADGE_RENDER_OBJECT_H

#include "sdl_badge_render_object.h"

class SDL_RectangleBadgeRenderObject : public SDL_BadgeRenderObject
{
public:
    SDL_RectangleBadgeRenderObject(const vec2 &position, const vec2 &size, sdl_data *color,int radius);

void render(SDLRenderer *,const mat2 &) override;

};
#endif //CONSTRUCT_AND_DESTROY_SDL_RECTANGLE_BADGE_RENDER_OBJECT_H
