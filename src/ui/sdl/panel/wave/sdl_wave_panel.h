//
// Created by robin on 5/16/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H

#include <string>
#include "sdl/panel/sdl_panel.h"

template<class T>
class StateMachine;

class Wave;

class SDLRenderSolidText;

class SDLWavePanel : public SDLPanel {
private:
    std::string _title, _max_wave, _current_wave, _modifier, _wave_time;

    Wave *_wave;
    StateMachine<SDLWavePanel> *_wave_panel_state_machine;

public:
    explicit SDLWavePanel(SDLRenderSolidText *, Wave *);

    void render(SDLRenderer *, float) override;

    Wave *get_wave();

    StateMachine<SDLWavePanel> *get_state_machine();
};

#endif //CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
