//
// Created by Jeroen on 5/11/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_BUILDING_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_BUILDING_PANEL_H

#include <sdl/event/slot/sdl_mouse_event_slot.h>
#include "sdl_panel.h"
#include <string>

class SDL_ImageRenderObject;
class BuildingEntity;

/**
 * Renders panels for all buildings that can be placed
 */
class SDLBuildingPanel : public SDLPanel {
private:
    std::vector<SDLPanel*> mouse_callbacks;
public:
    explicit SDLBuildingPanel(SDL_RenderObject *);
    ~SDLBuildingPanel();
    void render(SDLRenderer *renderer, float d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_BUILDING_PANEL_H
