//
// Created by robin on 5/17/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RENDER_SOLID_TEXT_H
#define CONSTRUCT_AND_DESTROY_SDL_RENDER_SOLID_TEXT_H

#include <string>
#include <SDL_ttf.h>
#include "sdl/sdl_render_object.h"

struct sdl_solid_text : public sdl_data {
    unsigned int font_size, padding;
    SDL_Color foreground, background;
    std::string font;
    std::string text;
    sdl_solid_text(SDL_Color, SDL_Color, std::string &, unsigned int, unsigned int, std::string &);
};

class SDLRenderSolidText : public SDL_RenderObject {
private:
    sdl_solid_text *_text_data;

    void draw_background(SDLRenderer *, const mat2 &);
    void draw_foreground(SDLRenderer *, const mat2 &);
public:
    explicit SDLRenderSolidText(const vec2 &, const vec2 &, sdl_solid_text *);

    ~SDLRenderSolidText();

    void render(SDLRenderer *, const mat2 &) override;

    sdl_solid_text *get_data() override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_RENDER_SOLID_TEXT_H
