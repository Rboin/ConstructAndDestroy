//
// Created by Sander on 18-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_IMAGE_HEALTH_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_IMAGE_HEALTH_RENDER_OBJECT_H

#include "sdl_image_render_object.h"

class BaseEntity;

class SDL_ImageHealthRenderObject : public SDL_ImageRenderObject {
private:
    BaseEntity *_owner;

public:
    SDL_ImageHealthRenderObject(const vec2 &position, const vec2 &size, sdl_image_data *data, BaseEntity*);

    ~SDL_ImageHealthRenderObject();

    void render(SDLRenderer *, const mat2 &) override;

    void draw_health_bar(SDLRenderer *, vec2);
};


#endif //CONSTRUCT_AND_DESTROY_SDL_IMAGE_HEALTH_RENDER_OBJECT_H
