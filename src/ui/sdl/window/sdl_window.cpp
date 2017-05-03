//
// Created by robin on 4/23/17.
//

#include "sdl_window.h"
#include "world/world.h"
#include "entity/player.h"

SDLWindow::SDLWindow(SDL_RenderObject *r) :
        SDLWindow(r, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window) :
        SDLWindow(r, sdl_window, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window, Renderer<SDL_Renderer> *renderer) :
        SDLWindow(r, sdl_window, renderer, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window, Renderer<SDL_Renderer> *renderer,
                     EventDispatcher<SDL_UIComponent, sdl_mouse_event_data> *mouse) :
        SDLWindow(r, sdl_window, renderer, mouse, nullptr) {}

SDLWindow::SDLWindow(SDL_RenderObject *r, SDL_Window *sdl_window, Renderer<SDL_Renderer> *renderer,
                     EventDispatcher<SDL_UIComponent, sdl_mouse_event_data> *mouse,
                     EventDispatcher<SDL_UIComponent, key_event_data> *key) : SDL_UIComponent(r) {
    _mouse_event_dispatcher = mouse;
    _key_event_dispatcher = key;
    _renderer = renderer;
    _sdl_window = sdl_window;
}

const float fps = 60;
const float minimumTimeFrame = 1000 / fps;

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
                    _mouse_event_dispatcher->dispatch({event.type, event.button.button, event.button.timestamp, mouse_position});
                }
            }
        }

        long current_tick = SDL_GetTicks();
        float delta = current_tick - last_tick;
        last_tick = current_tick;
        if (_renderer) {
            render(_renderer, delta);
        }

        //Wait a bit, so we don't update million of times per second
        if ((SDL_GetTicks() - current_tick) < minimumTimeFrame) {
            SDL_Delay(minimumTimeFrame - (SDL_GetTicks() - current_tick));
        }

    }
}

SDL_Texture *SDLWindow::render(Renderer<SDL_Renderer> *renderer, float delta) {
    SDL_RenderClear(renderer->get_engine());
    SDL_UIComponent::render(renderer, delta);
    SDL_RenderPresent(renderer->get_engine());
}