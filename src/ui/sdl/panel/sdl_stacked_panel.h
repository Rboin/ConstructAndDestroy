//
// Created by Jeroen on 6/1/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_STACKED_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_STACKED_PANEL_H

#include "sdl_panel.h"

enum Orientation {
    horizontal,
    vertical
};

class SDLStackedPanel : public SDLPanel {
private:
    Orientation _orientation;
public:
    SDLStackedPanel(SDL_RenderObject *, Orientation orientation);

    void render(SDLRenderer *renderer, mat2 &m, float d) override;

    void add_component(SDLPanel *child);
};


#endif //CONSTRUCT_AND_DESTROY_SDL_STACKED_PANEL_H
