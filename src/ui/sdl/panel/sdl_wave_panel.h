//
// Created by robin on 5/16/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H

#include "sdl_panel.h"
#include "state/state_machine.h"
#include "wave/wave.h"

class SDLWavePanel : public SDLPanel {
private:
    StateMachine<Wave> *_wave_machine;
public:
    explicit SDLWavePanel(SDL_RenderObject *);

};

#endif //CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
