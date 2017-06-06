//
// Created by Jeroen on 5/11/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_BUILDING_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_BUILDING_PANEL_H

#include "sdl_panel.h"

/**
 * Renders panels for all buildings that can be placed
 */
class SDLBuildingPanel : public SDLPanel {
public:
    explicit SDLBuildingPanel(SDL_RenderObject *);

    ~SDLBuildingPanel();

    void resize(const vec2 &) override;

    void render(SDLRenderer *renderer, mat2 &, float d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_BUILDING_PANEL_H
