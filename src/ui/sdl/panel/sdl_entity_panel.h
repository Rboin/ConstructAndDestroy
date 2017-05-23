//
// Created by Jeroen on 5/19/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H

#include "sdl_panel.h"

class BuildingEntity;

/**
 * Renders panels for all entities that can be spawned
 */
class SDLEntityPanel : public SDLPanel {
public:
    explicit SDLEntityPanel(SDL_RenderObject *, BuildingEntity* selected_building);
    void render(SDLRenderer *renderer, float d) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H
