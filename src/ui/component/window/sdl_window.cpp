//
// Created by robin on 4/23/17.
//

#include "sdl_window.h"

#include <SDL2/SDL.h>
#include "vector.h"

SDLWindow::SDLWindow(SDL_UI_RenderObject *r) : SDLWindow(r, nullptr) {}

SDLWindow::SDLWindow(SDL_UI_RenderObject *r, SDL_Window *sdl_window) : SDLWindow(r, sdl_window, nullptr) {}

SDLWindow::SDLWindow(SDL_UI_RenderObject *r, SDL_Window *sdl_window, EventDispatcher<mouse_event_data> *mouse) :
        SDLWindow(r, sdl_window, mouse, nullptr) {}

SDLWindow::SDLWindow(SDL_UI_RenderObject *r, SDL_Window *sdl_window, EventDispatcher<mouse_event_data> *mouse,
                     EventDispatcher<key_event_data> *key) : SDLWindow(r, sdl_window, mouse, key, nullptr) {}

SDLWindow::SDLWindow(SDL_UI_RenderObject *r, SDL_Window *sdl_window, EventDispatcher<mouse_event_data> *mouse,
                     EventDispatcher<key_event_data> *key, Renderer<SDL_Renderer> *renderer) : SDL_UIComponent(r) {
    _mouse_event_dispatcher = mouse;
    _key_event_dispatcher = key;
    _renderer = renderer;
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
                    _mouse_event_dispatcher->dispatch({event.type, event.button.timestamp, mouse_position});
                }
            }
        }

        long current_tick = SDL_GetTicks();
        float delta = current_tick - last_tick;
        if (_renderer) {
            render(_renderer, delta);
        }
    }
}

SDL_Texture *SDLWindow::render(Renderer<SDL_Renderer> *renderer, float delta) {

}






