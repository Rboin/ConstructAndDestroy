//
// Created by Stephan Schrijver on 1-6-2017.
//
#include <cstring>
#include "sdl_shortcut_badge_render_object.h"
#include "sdl/text/sdl_render_text_object.h"

SDL_ShortcutBadgeRenderObject::SDL_ShortcutBadgeRenderObject(const vec2 &position, const vec2 &size, TTF_Font *font, std::string text, sdl_data *color, int radius)
        : SDL_RectangleBadgeRenderObject(position, size, color, radius) {
    vec2 text_size = {(float)_radius, (float)_radius};
    vec2 text_pos = _center - vec2(text_size.x / 2, text_size.y / 2);
    _shortcut = text;
    sdl_data textcolor = sdl_data(0, 0, 0, 255);
    _textdata = new sdl_text{textcolor.red, textcolor.green, textcolor.blue, (_shortcut).c_str(), font};
    _text = new SDL_UI_RenderTextObject(text_pos, text_size, _textdata);
}

void SDL_ShortcutBadgeRenderObject::render(SDLRenderer * renderer, const mat2 &transformation) {
    SDL_RectangleBadgeRenderObject::render(renderer,transformation);
    _text->render(renderer,transformation);
}
