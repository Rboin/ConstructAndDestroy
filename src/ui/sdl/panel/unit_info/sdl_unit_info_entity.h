//
// Created by Jeroen on 6/6/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UNIT_INFO_ENTITY_H
#define CONSTRUCT_AND_DESTROY_SDL_UNIT_INFO_ENTITY_H

#include "sdl/panel/sdl_panel.h"

class MovingEntity;
class BaseEntity;
class SDLStackedPanel;
class SDLRenderLabel;

class SDLUnitInfoEntity : public SDLPanel {
private:
    SDLStackedPanel* _attributes_stackpanel;

    SDLStackedPanel* _stackpanel;

    BaseEntity *_entity;

    std::map<std::string, SDLRenderLabel *> _labels;
public:
    SDLUnitInfoEntity(MovingEntity* entity, SDL_RenderObject *r);

    SDLUnitInfoEntity(BuildingEntity *entity, SDL_RenderObject *r);

    SDLUnitInfoEntity(BaseEntity *entity, SDL_RenderObject *r, std::string texture);

    void render(SDLRenderer *renderer, mat2 &m, float d) override;

    void resize(const vec2 &) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_UNIT_INFO_ENTITY_H
