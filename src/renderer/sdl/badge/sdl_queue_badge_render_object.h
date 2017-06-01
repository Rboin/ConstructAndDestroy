//
// Created by Stephan Schrijver on 1-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_QUEUE_BADGE_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_QUEUE_BADGE_RENDER_OBJECT_H

#include <SDL_ttf.h>
#include "sdl_circle_badge_render_object.h"

class SDL_QueueBadgeRenderObject: public SDL_CircleBadgeRenderObject{
private:
    int _count;
public:
    SDL_QueueBadgeRenderObject(const vec2 &position, const vec2 &size, TTF_Font *font,
                                                             sdl_data *color, int radius);
    void update_count(int count);

    virtual void render(SDLRenderer*,const mat2 &) override;

};

#endif //CONSTRUCT_AND_DESTROY_SDL_QUEUE_BADGE_RENDER_OBJECT_H
