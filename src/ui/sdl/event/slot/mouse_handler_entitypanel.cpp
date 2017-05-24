//
// Created by Jeroen on 5/18/2017.
//

#include "manager/build_and_spawn_manager.h"
#include "mouse_handler_entitypanel.h"

MouseHandlerEntityPanel::MouseHandlerEntityPanel() {
}

MouseHandlerEntityPanel::~MouseHandlerEntityPanel() {}


void MouseHandlerEntityPanel::handle_up(SDLUnitPanel *sdl_panel) {
    BuildAndSpawnManager::get_instance()->spawn_spawnable_entity(sdl_panel);
}


void MouseHandlerEntityPanel::on(sdl_mouse_event_data data) {
    SDLUnitPanel *sdl_panel = (SDLUnitPanel *) data.component;
    if (data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP) {
        handle(data, sdl_panel);
    }
}

void MouseHandlerEntityPanel::handle(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    switch (data.button) {
        case SDL_BUTTON_LEFT:
            if (data.type == SDL_MOUSEBUTTONUP) {
                return handle_up(sdl_panel);
            }

            return;

        default:
            return;
    }
}