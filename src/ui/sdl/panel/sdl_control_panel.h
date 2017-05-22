//
// Created by Jeroen on 5/19/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_CONTROL_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_CONTROL_PANEL_H

#include "sdl/event/slot/sdl_mouse_event_slot.h"
#include "sdl_panel.h"
#include <string>

class SDL_RenderObject;

/**
 * Either renders the SDLBuildingPanel or the SDLEntityPanel
 * based on whether or not a building has been selected at that time
 */
class SDLControlPanel : public SDLPanel {
private:
    SDL_RenderObject* get_similar_representation();
public:
    explicit SDLControlPanel(SDL_RenderObject *);
    void render(SDLRenderer *renderer, float d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_CONTROL_PANEL_H
