//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H

#include <SDL2/SDL.h>
#include <cstdint>
#include "render_object.h"

class SDLRenderer;

struct sdl_data {
    uint8_t red, green, blue, alpha;
    sdl_data(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};

class SDL_RenderObject : public RenderObject<SDLRenderer, sdl_data, SDL_Texture> {
protected:
    SDL_Rect *rectangle;
public:
    SDL_RenderObject(const vec2 &position, const vec2 &size, sdl_data *data);

    void render(SDLRenderer *t) override;

    virtual void init_texture(SDLRenderer *);

    void clear_texture(SDLRenderer *, SDL_Rect *);

    void clear_data() override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H
