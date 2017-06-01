//
// Created by Mark on 23-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_COST_LABEL_H
#define CONSTRUCT_AND_DESTROY_SDL_COST_LABEL_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include "sdl/sdl_render_object.h"
#include "entity/static/resource_type.h"

class SDL_UI_RenderTextObject;
class SDL_ImageRenderObject;
class Resources;

class SDLCostLabel : public SDL_RenderObject {
private:
    SDL_UI_RenderTextObject *_text;
    SDL_ImageRenderObject *_image;
    ResourceType _rt;
    Resources* _resources;
    sdl_data* data;
public:
    SDLCostLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string, ResourceType, TTF_Font *, Resources* resources);

    ~SDLCostLabel();

    void render(SDLRenderer *renderer) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_COST_LABEL_H
