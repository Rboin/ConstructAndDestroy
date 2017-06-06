//
// Created by robin on 4/26/17.
//

#include "sdl_image_render_object.h"
#include "textures/texture_manager.h"
#include "sdl/sdl_renderer.h"
#include "matrix.h"

SDL_ImageRenderObject::SDL_ImageRenderObject(const vec2 &position, const vec2 &size, sdl_image_data *data)
        : SDL_RenderObject(position, size, data) {}

SDL_ImageRenderObject::~SDL_ImageRenderObject() {
    clear_data();
}

void SDL_ImageRenderObject::render(SDLRenderer *renderer, const mat2 &transformations) {
    if (!_result) {
        init_texture(renderer);
    }

    renderer->draw_to_buffer(_result, &get_transformed_rectangle(transformations));
}

void SDL_ImageRenderObject::init_texture(SDLRenderer *renderer) {
    sdl_image_data *data = (sdl_image_data *) _data;
    _result = TextureManager::get_instance()->load_texture(data->type);
}

void SDL_ImageRenderObject::clear_data() {
    SDL_DestroyTexture(_result);
    _result = NULL;
}
