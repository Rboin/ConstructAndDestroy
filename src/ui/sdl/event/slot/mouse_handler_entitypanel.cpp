//
// Created by Jeroen on 5/18/2017.
//

#include "sdl/label/manager/description_manager.h"
#include "sdl/label/sdl_name_label.h"
#include "mouse_handler_entitypanel.h"
#include "manager/build_and_spawn_manager.h"
#include "../../../../logic/entity/moving/spawnable_entity.h"

MouseHandlerEntityPanel::MouseHandlerEntityPanel() {
}

MouseHandlerEntityPanel::~MouseHandlerEntityPanel() {}

void MouseHandlerEntityPanel::handle_up(SDLUnitPanel *sdl_panel) {
    BuildAndSpawnManager::get_instance()->spawn_spawnable_entity(sdl_panel);
}


void MouseHandlerEntityPanel::on(sdl_mouse_event_data data) {
    SDLUnitPanel *sdl_panel = (SDLUnitPanel *) data.component;

    if( data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP){
        handle(data, sdl_panel);
    } else if (data.type == SDL_MOUSEMOTION) {
        handle_motion(data, sdl_panel);
    }
}

void MouseHandlerEntityPanel::handle(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    switch (data.type) {
        case SDL_MOUSEBUTTONUP:
            return handle_up(sdl_panel);
        case SDL_MOUSEMOTION:
            return handle_motion(data, sdl_panel);
        default:
            return;
    }
}

void MouseHandlerEntityPanel::handle_motion(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {

    //define rectangle when to show description
    float top = sdl_panel->get_position()->y + 10;
    float left = sdl_panel->get_position()->x + 10;
    float bot = top + sdl_panel->get_size()->y - 10;
    float right = left + sdl_panel->get_size()->x -20;

    float x = data.position.x, y = data.position.y;

    if(x >= left && x <= right && y >= top && y <= bot){
        DescriptionManager::get_description()->set_text(sdl_panel->get_spawnable_entity()->get_description());
    } else {
        DescriptionManager::get_description()->set_text("");
    }
}
