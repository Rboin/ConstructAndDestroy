//
// Created by robin on 5/17/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_PANEL_PREPARATION_H
#define CONSTRUCT_AND_DESTROY_WAVE_PANEL_PREPARATION_H

#include "state/state.h"
#include "sdl/panel/wave/sdl_wave_panel.h"

class Wave;

struct sdl_solid_text;

class WavePanelPreparing : public State<SDLWavePanel> {
private:
    void update_text(Wave *, sdl_solid_text *);

public:
    void enter(SDLWavePanel *t) override;

    void execute(SDLWavePanel *t) override;

    void exit(SDLWavePanel *t) override;

    std::string update_wave_time(Wave *wave);
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_PANEL_PREPARATION_H
