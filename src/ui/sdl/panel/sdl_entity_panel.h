//
// Created by Jeroen on 5/19/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H

#include "sdl/event/slot/sdl_mouse_event_slot.h"
#include "sdl_panel.h"
#include <string>

class SDL_ImageRenderObject;
class BuildingEntity;

/**
 * Renders panels for all entities that can be spawned
 */
class SDLEntityPanel : public SDLPanel {
private:
    std::vector<SDLPanel*> mouse_callbacks;
public:
    explicit SDLEntityPanel(SDL_RenderObject *, BuildingEntity* selected_building);
    ~SDLEntityPanel();
    void render(SDLRenderer *renderer, float d) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H
