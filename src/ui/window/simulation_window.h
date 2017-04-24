//
// Created by robin on 3/19/17.
//

#ifndef C_AND_D_PROJECT_SIMULATION_WINDOW_H
#define C_AND_D_PROJECT_SIMULATION_WINDOW_H


#include "ui_component.h"

struct SDL_Window;

class SimulationWindow : public UIComponent {
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
public:
    SimulationWindow(SDL_Window *, SDL_Renderer *, SDL_Rect *);

    void draw();

    SDL_Texture *draw(SDL_Renderer *renderer) override;

    void update(float d) override;
};


#endif //C_AND_D_PROJECT_SIMULATION_WINDOW_H
