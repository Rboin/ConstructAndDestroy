//
// Created by Jeroen on 5/19/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_CONTROL_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_CONTROL_PANEL_H

#include "sdl_panel.h"
#include <string>

class SDL_RenderObject;

/**
 * Either renders the SDLBuildingPanel or the SDLEntityPanel
 * based on whether or not a building has been selected at that time
 */
class SDLControlPanel : public SDLPanel {
private:
    static SDLControlPanel* _instance;
    explicit SDLControlPanel(SDL_RenderObject *);
    SDL_RenderObject* get_similar_representation();
public:
    static SDLControlPanel* get_instance(SDL_RenderObject*);
    static SDLControlPanel* get_instance();
    ~SDLControlPanel();
    void render(SDLRenderer *renderer, float d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_CONTROL_PANEL_H
