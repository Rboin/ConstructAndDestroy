//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H

#include <SDL2/SDL.h>
#include <cstdint>
#include "types.h"
#include "render_object.h"

struct sdl_ui_data {
    uint8_t red, green, blue;
};

struct SDL_Renderer;


class SDL_UI_RenderObject : public RenderObject<SDL_Renderer, sdl_ui_data, SDL_Texture> {
public:
    SDL_UI_RenderObject(const vec2 &position, const vec2 &size, const sdl_ui_data &data);

    SDL_Texture *render(Renderer<SDL_Renderer> *renderer) override;

    void init_texture(Renderer<SDL_Renderer> *);
    void clear_texture(Renderer<SDL_Renderer> *, SDL_Rect *);
};


#endif //CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_OBJECT_H
