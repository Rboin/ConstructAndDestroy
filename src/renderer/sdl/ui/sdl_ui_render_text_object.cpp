//
// Created by robin on 4/26/17.
//

#include "sdl_ui_render_text_object.h"
#include "renderer.h"

SDL_UI_RenderTextObject::SDL_UI_RenderTextObject(const vec2 &position, const vec2 &size, sdl_ui_text_data *data) :
        SDL_RenderObject(position, size, data) {}

SDL_Texture *SDL_UI_RenderTextObject::render(Renderer<SDL_Renderer> *renderer) {
    if (!_result) {
        init_texture(renderer);
    }
    return _result;
}

void SDL_UI_RenderTextObject::init_texture(Renderer<SDL_Renderer> *renderer) {
    // Casts the _data pointer to text data pointer, since this is what we gave the component.
    sdl_ui_text_data *data = (sdl_ui_text_data *) _data;
    SDL_Surface *text_surface = TTF_RenderText_Shaded(data->font, data->text,
                                                      {0, 0, 0},
                                                      {data->red, data->green, data->blue});
    _result = SDL_CreateTextureFromSurface(renderer->get_engine(), text_surface);
    SDL_FreeSurface(text_surface);
}