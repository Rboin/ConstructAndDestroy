//
// Created by robin on 3/19/17.
//

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>
#include <iostream>
#include "logic/graph/graph_manager.h"
#include "ui/eventhandler/mouse_handler.h"
#include "logic/entity/moving/moving_entity.h"
#include "ui/panel/information_panel.h"

#include "simulation.h"
#include "ui/window/simulation_window.h"
#include "ui/eventhandler/key_handler.h"


Simulation::Simulation(SimulationWindow *window) {
    _window = window;
}

Simulation::~Simulation() {
//    delete _window;
}

const float fps = 60;
const float minimumTimeFrame = 1000 / fps;
bool isRunning = true;

void Simulation::loop() {
    long last = SDL_GetTicks();
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return;
            else if (event.type == SDL_KEYDOWN) {
                key_event_data d;
                d.data = event.key.keysym.sym;
                _key_handler->handle(d);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouse_event_data d;
                d.data = event.button;
                d.graph = GraphManager::get_instance()->graph;
                _mouse_handler->handle(d);
            }
        }

        long current_time = SDL_GetTicks();
        float delta = current_time - last;
        last = current_time;

        _window->update(delta);

        //Wait a bit, so we don't update million of times per second
        if((SDL_GetTicks() - current_time) < minimumTimeFrame){
            SDL_Delay(minimumTimeFrame - (SDL_GetTicks() - current_time));
        }

        _window->draw();
    }
}

void Simulation::set_key_handler(EventHandler<key_event_data> *k_h) {
    _key_handler = k_h;
}

void Simulation::set_mouse_handler(EventHandler<mouse_event_data> *m_h) {
    _mouse_handler = m_h;
}

