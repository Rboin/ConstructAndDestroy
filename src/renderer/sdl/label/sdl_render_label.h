//
// Created by bouwm on 8-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RENDER_LABEL_H
#define CONSTRUCT_AND_DESTROY_SDL_RENDER_LABEL_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include "sdl/sdl_render_object.h"

class SDL_UI_RenderTextObject;

class SDL_ImageRenderObject;

class Resources;

class SDLRenderLabel : public SDL_RenderObject {
private:
    SDL_UI_RenderTextObject *_text;
    SDL_ImageRenderObject *_image;
public:
    SDLRenderLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string texture,std::string, TTF_Font *);

    ~SDLRenderLabel();

    void render(SDLRenderer *renderer, const mat2 &) override;

    void set_position(float x, float y) override;

    void set_text(const char* text);
};


#endif //CONSTRUCT_AND_DESTROY_SDL_RENDER_LABEL_H
