//
// Created by robin on 5/17/17.
//

#include <iostream>
#include "sdl_render_solid_text.h"
#include "sdl/sdl_renderer.h"

sdl_solid_text::sdl_solid_text(SDL_Color b, SDL_Color f, std::string &font_path, unsigned int pt,
                               unsigned int pad, std::string &s)
    : sdl_data(0, 0, 0, 0) {
    background = b;
    foreground = f;
    font = font_path;
    font_size = pt;
    padding = pad;
    text = s;
}

SDLRenderSolidText::SDLRenderSolidText(const vec2 &position, const vec2 &size, sdl_solid_text *data)
    : SDL_RenderObject(position, size, nullptr) {
    _text_data = data;
}

SDLRenderSolidText::~SDLRenderSolidText() {
    delete _text_data;
}

void SDLRenderSolidText::render(SDLRenderer *renderer) {
    draw_background(renderer);
    draw_foreground(renderer);
}

void SDLRenderSolidText::draw_background(SDLRenderer *renderer) {
    SDL_SetRenderDrawColor(renderer->get_engine(), _text_data->background.r, _text_data->background.g,
                           _text_data->background.b, _text_data->background.a);
    SDL_RenderFillRect(renderer->get_engine(), rectangle);
}

void SDLRenderSolidText::draw_foreground(SDLRenderer *renderer) {
    TTF_Font *font = TTF_OpenFont(_text_data->font.c_str(), _text_data->font_size);
    if(!font) {
        std::cout << "Could not open font: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(font, _text_data->text.c_str(),
                                                               _text_data->foreground, (Uint32) _size.x);

    if(!text_surface) {
        std::cout << "Unable to load text surface: " << SDL_GetError() << std::endl;
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer->get_engine(), text_surface);

    SDL_Rect padded_rect = {
        (int) (_position.x + _text_data->padding), (int) (_position.y + _text_data->padding),
        (int) (_size.x - (_text_data->padding * 2)), (int) (_size.y - (_text_data->padding * 2))
    };

    renderer->draw_to_back_buffer(text_texture, &padded_rect);

    // Destroy the textures and font
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
}

sdl_solid_text *SDLRenderSolidText::get_data() {
    return _text_data;
}
