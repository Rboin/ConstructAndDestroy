//
// Created by robin on 5/24/17.
//

#ifndef CONSTRUCT_AND_DESTROY_RESTART_WAVE_BUTTON_H
#define CONSTRUCT_AND_DESTROY_RESTART_WAVE_BUTTON_H

#include "sdl_button.h"

class RestartWaveButton : public SDLButton {
public:
    explicit RestartWaveButton(SDL_RenderObject *);

    void resize(const vec2 &vec21) override;

    void render(SDLRenderer *t, mat2 &mat21, float d) override;
};

#endif //CONSTRUCT_AND_DESTROY_RESTART_WAVE_BUTTON_H
