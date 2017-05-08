//
// Created by bouwm on 8-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RENDER_LABEL_H
#define CONSTRUCT_AND_DESTROY_SDL_RENDER_LABEL_H


#include <sdl/sdl_render_object.h>
#include <sdl/image/sdl_image_render_object.h>
#include <sdl/ui/sdl_ui_render_text_object.h>
#include "entity/static/resource_type.h"

class Resources;

class SDLRenderLabel : public SDL_RenderObject {
private:
    SDL_UI_RenderTextObject *_text;
    SDL_ImageRenderObject *_image;
    Resources *_resource;
    ResourceType &_rt;
public:
    SDLRenderLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string, ResourceType, TTF_Font *);

    SDL_Texture *render(Renderer<SDL_Renderer> *renderer) override;

};


#endif //CONSTRUCT_AND_DESTROY_SDL_RENDER_LABEL_H
