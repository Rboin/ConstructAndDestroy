//
// Created by robin on 4/26/17.
//

#include <textures/texture_manager.h>
#include "sdl_image_render_object.h"
#include "sdl/sdl_renderer.h"

SDL_ImageRenderObject::SDL_ImageRenderObject(const vec2 &position, const vec2 &size, sdl_image_data *data)
        : SDL_RenderObject(position, size, data) {}

void SDL_ImageRenderObject::render(SDLRenderer *renderer) {
    if (!_result) {
        init_texture(renderer);
    }
    rectangle->x = (int) _position.x;
    rectangle->y = (int) _position.y;

    renderer->draw_to_back_buffer(_result, rectangle);
}

void SDL_ImageRenderObject::init_texture(SDLRenderer *renderer) {
    sdl_image_data *data = (sdl_image_data *) _data;
    _result = TextureManager::get_instance()->loadTexture(data->type);
}

void SDL_ImageRenderObject::clear_data() {
    SDL_DestroyTexture(_result);
    _result = NULL;
}
