//
// Created by Stephan Schrijver on 1-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_CIRCLE_BADGE_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_CIRCLE_BADGE_RENDER_OBJECT_H

#include "sdl_badge_render_object.h"

class SDL_CircleBadgeRenderObject : public SDL_BadgeRenderObject {
public:
    SDL_CircleBadgeRenderObject(const vec2 &position, const vec2 &size, sdl_data *color, int radius);

    ~SDL_CircleBadgeRenderObject();

    void render(SDLRenderer *,  const mat2 &) override;

};

#endif //CONSTRUCT_AND_DESTROY_SDL_CIRCLE_BADGE_RENDER_OBJECT_H
