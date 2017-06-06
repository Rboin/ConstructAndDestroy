//
// Created by robin on 5/16/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H

#include "sdl/panel/sdl_panel.h"

template<class T>
class StateMachine;
class SDLRenderSolidText;
class WaveManager;
class Wave;

class SDLWavePanel : public SDLPanel {
private:
    WaveManager *_wave_manager;
    StateMachine<SDLWavePanel> *_wave_panel_state_machine;

public:
    explicit SDLWavePanel(SDLRenderSolidText *, WaveManager *);

    ~SDLWavePanel();

    void render(SDLRenderer *, mat2 &, float) override;

    Wave *get_wave();

    StateMachine<SDLWavePanel> *get_state_machine();

    void resize(const vec2 &) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
