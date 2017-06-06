//
// Created by Mark on 29-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_NAME_LABEL_H
#define CONSTRUCT_AND_DESTROY_SDL_NAME_LABEL_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include "sdl/sdl_render_object.h"
#include "entity/static/resource_type.h"

class SDL_UI_RenderTextObject;
class Resources;

class SDLNameLabel : public SDL_RenderObject {
private:
    SDL_UI_RenderTextObject *_text_object;
    std::string _text;

public:
    SDLNameLabel(const vec2 &position, const vec2 &size, sdl_data *data, TTF_Font* font, std::string text);

    ~SDLNameLabel();

    void render(SDLRenderer *renderer, const mat2 &) override;

    void set_text(std::string text);

    void set_position(float x, float y) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_NAME_LABEL_H
