//
// Created by robin on 4/23/17.
//

#include "sdl_ui_render_object.h"

SDL_UI_RenderObject::SDL_UI_RenderObject(const vec2 &position, const vec2 &size, const sdl_ui_data &data)
        : RenderObject(position, size, data) {}

SDL_Texture *SDL_UI_RenderObject::render(Renderer<SDL_Renderer> *renderer) {
    return nullptr;
}
