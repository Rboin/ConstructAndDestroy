//
// Created by robin on 5/17/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_PANEL_SPAWNING_H
#define CONSTRUCT_AND_DESTROY_WAVE_PANEL_SPAWNING_H

#include "state/state.h"
#include "sdl/panel/wave/sdl_wave_panel.h"

class Wave;

struct sdl_solid_text;

class WavePanelSpawning : public State<SDLWavePanel> {
private:
    void update_text(Wave *, sdl_solid_text *);

    std::string update_wave_time(Wave *wave);

    std::string update_stat_modifier(Wave *wave);

public:
    void enter(SDLWavePanel *t) override;

    void execute(SDLWavePanel *t) override;

    void exit(SDLWavePanel *t) override;
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_PANEL_SPAWNING_H
