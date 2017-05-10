//
// Created by robin on 4/26/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_TEXT_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_TEXT_OBJECT_H

#include <SDL2/SDL_ttf.h>
#include "sdl/sdl_render_object.h"

struct sdl_ui_text_data : public sdl_data {
    const char *text;
    TTF_Font *font;

    sdl_ui_text_data(uint8_t r, uint8_t g, uint8_t b, const char *c, TTF_Font *f) : sdl_data(r, g, b) {
        text = c;
        font = f;
    }
};

class SDL_UI_RenderTextObject : public SDL_RenderObject {
public:
    SDL_UI_RenderTextObject(const vec2 &position, const vec2 &size, sdl_ui_text_data *data);

    void render(SDLRenderer *) override;

    void init_texture(SDLRenderer *renderer) override;

    void clear_result();
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_TEXT_OBJECT_H
