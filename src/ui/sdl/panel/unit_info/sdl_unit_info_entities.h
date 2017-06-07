//
// Created by Jeroen on 6/6/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UNIT_INFO_ENTITIES_H
#define CONSTRUCT_AND_DESTROY_SDL_UNIT_INFO_ENTITIES_H

#include <vector>
#include "sdl/panel/sdl_panel.h"

class MovingEntity;

class SDLUnitInfoEntities : public SDLPanel {
public:
    SDLUnitInfoEntities(std::vector<MovingEntity *> entities, SDL_RenderObject *r);

    void render(SDLRenderer *renderer, mat2 &m, float d) override;

    void resize(const vec2 &) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_UNIT_INFO_ENTITIES_H
