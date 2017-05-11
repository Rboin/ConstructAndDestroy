//
// Created by robin on 4/26/17.
//

#include "sdl_ui_render_text_object.h"
#include "sdl/sdl_renderer.h"

SDL_UI_RenderTextObject::SDL_UI_RenderTextObject(const vec2 &position, const vec2 &size, sdl_ui_text_data *data) :
        SDL_RenderObject(position, size, data) {
}

void SDL_UI_RenderTextObject::render(SDLRenderer *renderer) {
    clear_result();
    init_texture(renderer);
    renderer->draw_to_back_buffer(_result, rectangle);
}

void SDL_UI_RenderTextObject::init_texture(SDLRenderer *renderer) {
    // Casts the _data pointer to text data pointer, since this is what we gave the component.
    sdl_ui_text_data *data = (sdl_ui_text_data *) _data;
    SDL_Surface *text_surface = TTF_RenderText_Blended(data->font, data->text,
                                                       {data->red, data->green, data->blue, data->alpha});
    _result = SDL_CreateTextureFromSurface(renderer->get_engine(), text_surface);
    SDL_FreeSurface(text_surface);

}

void SDL_UI_RenderTextObject::clear_result() {
    SDL_DestroyTexture(_result);
    _result = nullptr;
}