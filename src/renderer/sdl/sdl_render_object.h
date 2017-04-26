//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H

#include <SDL2/SDL.h>
#include <cstdint>
#include "types.h"
#include "render_object.h"

struct SDL_Renderer;

struct sdl_data {
    uint8_t red, green, blue;
};

class SDL_RenderObject : public RenderObject<SDL_Renderer, sdl_data, SDL_Texture> {
public:
    SDL_RenderObject(const vec2 &position, const vec2 &size, sdl_data *data);

    SDL_Texture *render(Renderer<SDL_Renderer> *renderer) override;

    virtual void init_texture(Renderer<SDL_Renderer> *);

    void clear_texture(Renderer<SDL_Renderer> *, SDL_Rect *);
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H
