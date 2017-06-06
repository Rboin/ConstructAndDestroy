//
// Created by robin on 6/3/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RESOURCE_LABEL_H
#define CONSTRUCT_AND_DESTROY_SDL_RESOURCE_LABEL_H

#include "sdl_panel.h"

class SDLResourceLabel : public SDLPanel {
public:
    SDLResourceLabel(SDL_RenderObject *);

    void resize(const vec2 &) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_RESOURCE_LABEL_H
