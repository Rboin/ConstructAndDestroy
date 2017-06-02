//
// Created by robin on 4/26/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_IMAGE_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_IMAGE_RENDER_OBJECT_H

#include <string>
#include "textures/texture_types.h"
#include "sdl/sdl_render_object.h"

struct sdl_image_data : public sdl_data {
    std::string type;

    sdl_image_data(const std::string t) : sdl_data(0, 0, 0) {
        type = t;
    }

    virtual ~sdl_image_data() {

    }
};

class SDL_ImageRenderObject : public SDL_RenderObject {
public:
    SDL_ImageRenderObject(const vec2 &position, const vec2 &size, sdl_image_data *data);

    virtual ~SDL_ImageRenderObject();

    void render(SDLRenderer *) override;

    void init_texture(SDLRenderer *) override;

    void clear_data() override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_IMAGE_RENDER_OBJECT_H
