//
// Created by robin on 4/23/17.
//

#include <sdl/event/sdl_mouse_event_dispatcher.h>
#include "sdl_window.h"
#include "world/world.h"
#include "sdl/event/sdl_event_types.h"
#include "sdl/sdl_renderer.h"

SDLWindow::SDLWindow(SDL_RenderObject *r) :
        SDLWindow(r, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window) :
        SDLWindow(r, sdl_window, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window, SDLRenderer *renderer) :
        SDLWindow(r, sdl_window, renderer, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window, SDLRenderer *renderer,
                     EventDispatcher<SDL_UIComponent, sdl_mouse_event_data> *mouse) :
        SDLWindow(r, sdl_window, renderer, mouse, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window, SDLRenderer *renderer,
                     EventDispatcher<SDL_UIComponent, sdl_mouse_event_data> *mouse,
                     EventDispatcher<SDL_UIComponent, sdl_key_event_data> *key) : SDL_UIComponent(r) {
    _mouse_event_dispatcher = mouse;
    _key_event_dispatcher = key;
    _renderer = renderer;
    _sdl_window = sdl_window;
}

int SDLWindow::show() {
    long last_tick = SDL_GetTicks();

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                if (_key_event_dispatcher) {
                    _key_event_dispatcher->dispatch({event.type, event.key.timestamp, (char) event.key.keysym.sym});
                }
            } else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN ||
                       event.type == SDL_MOUSEBUTTONUP) {
                vec2 mouse_position = {(float) event.button.x, (float) event.button.y};
                if (_mouse_event_dispatcher) {
                    _mouse_event_dispatcher->dispatch(
                            {event.type, event.button.button, event.button.timestamp, mouse_position});
                }
            }
        }

        long current_tick = SDL_GetTicks();
        float delta = current_tick - last_tick;
        last_tick = current_tick;
        if (_renderer) {
            render(_renderer, delta);
        }
    }
}

void SDLWindow::render(SDLRenderer *renderer, float delta) {
    renderer->clear();
    SDL_UIComponent::render(renderer, delta);
    renderer->show();
}

SDLWindow::~SDLWindow() {
    SDL_DestroyRenderer(_renderer->get_engine());
    if(_renderer) {
        delete _renderer;
    }
    SDL_DestroyWindow(_sdl_window);
    _mouse_event_dispatcher = nullptr;
    _key_event_dispatcher = nullptr;
}
