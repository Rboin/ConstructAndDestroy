//
// Created by Jeroen on 6/1/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_UNIT_INFO_PANEL_H
#define CONSTRUCT_AND_DESTROY_UNIT_INFO_PANEL_H

#include "sdl_panel.h"

class BuildingEntity;
class MovingEntity;
class SDLStackedPanel;

class SDLUnitInfoPanel : public SDLPanel {
private:
    std::string _previous_units_hash;

    BuildingEntity *_previous_building;

    SDL_RenderObject* get_similar_representation();
public:
    void render(SDLRenderer *renderer, mat2 &m, float d) override;

    SDLUnitInfoPanel(SDL_RenderObject *r);
};


#endif //CONSTRUCT_AND_DESTROY_UNIT_INFO_PANEL_H
