//
// Created by robin on 4/23/17.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sdl/event/slot/sdl_mouse_event_slot.h>
#include "sdl/window/sdl_window.h"
#include "sdl/panel/sdl_panel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "world/world.h"

int pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 4;

SDL_Window *window;
SDL_Renderer *renderer;
World world1;

bool init_sdl() {
    if (SDL_Init(0) == -1) {
        std::cout << " Failed to open SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_window() {
    window = SDL_CreateWindow("Construct And Destroy", pos_x, pos_y, size_x, size_y, 0);

    if (!window) {
        std::cout << " Failed to open window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_renderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << " Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void setup_renderer() {
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize(renderer, size_x, size_y);
    // Set color of renderer to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
}

bool init_font() {
    if (TTF_Init() == -1) {
        std::cout << "Failed to initialize font: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer() || !init_font())
        return false;
    setup_renderer();
    return true;
}

int main(int argc, char **argv) {
    if (!init_everything()) {
        return -1;
    }

    SDL_Color f_color = {0, 0, 0, 255};
    TTF_Font *f_font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 16);

    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();

    Renderer<SDL_Renderer> r = Renderer<SDL_Renderer>(renderer);

    vec2 main_window_position = {0, 0}, main_window_size = {800, 600};
    sdl_ui_data main_window_data = {255, 255, 255};
    SDL_UI_RenderObject window_o = SDL_UI_RenderObject(main_window_position, main_window_size, main_window_data);
    SDLWindow sdl_window(&window_o, window, &r, mouse_dispatcher);

    vec2 right_panel_pos = {600, 0}, right_panel_size = {200, 600};
    sdl_ui_data right_panel_data = {0, 0, 255};
    SDL_UI_RenderObject panel_o = SDL_UI_RenderObject(right_panel_pos, right_panel_size, right_panel_data);
    SDLPanel right_panel(&panel_o);

    vec2 right_panel_top_pos = {601, 1}, right_panel_top_size = {200, 200};
    sdl_ui_data right_panel_top_data = {1, 255, 0};
    SDL_UI_RenderObject panel_top_o = SDL_UI_RenderObject(right_panel_top_pos, right_panel_top_size, right_panel_top_data);
    SDLPanel right_panel_top(&panel_top_o);

    SDL_MouseEventSlot *right_panel_slot = new SDL_MouseEventSlot();

    right_panel_top.set_mouse_callback(right_panel_slot);

    right_panel.set_mouse_callback(right_panel_slot);

    sdl_window.set_mouse_callback(right_panel_slot);

    mouse_dispatcher->register_callback(&right_panel_top, right_panel_slot);
    mouse_dispatcher->register_callback(&right_panel, right_panel_slot);
    mouse_dispatcher->register_callback(&sdl_window, right_panel_slot);

    right_panel.add_component(&right_panel_top);
    sdl_window.add_component(&right_panel);


    return sdl_window.show();
}