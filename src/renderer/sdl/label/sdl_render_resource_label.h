//
// Created by Jeroen on 6/1/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RENDER_RESOURCE_LABEL_H
#define CONSTRUCT_AND_DESTROY_SDL_RENDER_RESOURCE_LABEL_H


#include "entity/static/resource_type.h"
#include "sdl_render_label.h"

class SDLRenderResourceLabel : public SDLRenderLabel {
private:
    Resources *_resource;

    ResourceType _rt;

    const char *get_resource_text();
public:
    SDLRenderResourceLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string, ResourceType, TTF_Font *);

    void render(SDLRenderer *renderer, const mat2 &) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_RENDER_RESOURCE_LABEL_H
