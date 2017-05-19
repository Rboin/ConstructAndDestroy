//
// Created by Jeroen on 5/19/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_PANEL_H

#include "sdl_panel.h"

class SDL_ProgressbarRenderObject;
class SDLPanel;

/**
 * Either renders the SDLBuildingPanel or the SDLEntityPanel
 * based on whether or not a building has been selected at that time
 */
class SDLProgressBarPanel : public SDLPanel {
private:
    SDLPanel* _parent;
    bool _finished;
    float _targetDuration;
    float _elapsedDuration;
public:
    explicit SDLProgressBarPanel(SDL_ProgressbarRenderObject *, float duration, SDLPanel* parent);
    void render(SDLRenderer *renderer, float d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_PANEL_H
