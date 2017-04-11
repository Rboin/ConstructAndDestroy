//
// Created by robin on 3/19/17.
//

#include "simulation_window.h"

#include <SDL2/SDL.h>

SimulationWindow::SimulationWindow(SDL_Window *window, SDL_Renderer *renderer, SDL_Rect *s) : UIComponent(s) {
    _window = window;
    _renderer = renderer;
}

void SimulationWindow::draw() {
    SDL_RenderClear(_renderer);
    draw(_renderer);
    SDL_RenderPresent(_renderer);
}

void SimulationWindow::update(float d) {
    UIComponent::update(d);
}

SDL_Texture *SimulationWindow::draw(SDL_Renderer *renderer) {
    return UIComponent::draw(renderer);
}
