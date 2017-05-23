//
// Created by robin on 5/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_PANEL_FINISHED_H
#define CONSTRUCT_AND_DESTROY_WAVE_PANEL_FINISHED_H

#include "state/state.h"
#include "sdl/panel/wave/sdl_wave_panel.h"

struct sdl_solid_text;
class Wave;

class WavePanelFinished : public State<SDLWavePanel> {
private:
    void update_text(Wave *, sdl_solid_text *);
public:
    void enter(SDLWavePanel *t) override;

    void execute(SDLWavePanel *t) override;

    void exit(SDLWavePanel *t) override;
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_PANEL_FINISHED_H
