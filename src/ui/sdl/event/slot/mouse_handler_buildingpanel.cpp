//
// Created by Jeroen on 5/11/2017.
//

#include "manager/build_and_spawn_manager.h"
#include "sdl/label/manager/description_manager.h"
#include "sdl/label/sdl_name_label.h"
#include "sdl/event/sdl_event_types.h"
#include "sdl/panel/sdl_unit_panel.h"
#include "entity/player_manager.h"
#include "entity/static/building/building_state/choosing_building_position.h"
#include "entity/static/building/building_state/placing_building.h"
#include "entity/static/building/building_manager.h"
#include "mouse_handler_buildingpanel.h"
#include "world/world.h"
#include "entity/player.h"
#include "state/state_machine.h"

MouseHandlerBuildingPanel::MouseHandlerBuildingPanel() {

}

MouseHandlerBuildingPanel::~MouseHandlerBuildingPanel() {}

void MouseHandlerBuildingPanel::handle_up(SDLUnitPanel *sdl_panel) {
    BuildAndSpawnManager::get_instance()->build_building(sdl_panel);
}


void MouseHandlerBuildingPanel::on(sdl_mouse_event_data data) {
    SDLUnitPanel *sdl_panel = (SDLUnitPanel *) data.component;
    if( data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP){
        handle(data, sdl_panel);
    } else if (data.type == SDL_MOUSEMOTION) {
        handle_motion(data, sdl_panel);
    }
}

void MouseHandlerBuildingPanel::handle(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    vec2 pos = data.position;

    switch(data.button) {
        case SDL_BUTTON_LEFT:
            if (data.type == SDL_MOUSEBUTTONUP) {
                return handle_up(sdl_panel);
            }

            return;

        default:
            return;
    }
}

void MouseHandlerBuildingPanel::handle_motion(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    //define rectangle when to show description
    float top = sdl_panel->get_position()->y + 10;
    float bot = top + sdl_panel->get_size()->y - 10;

    float left = sdl_panel->get_position()->x + 10;
    float right = left + sdl_panel->get_size()->x - 20;

    float x = data.position.x, y = data.position.y;

    if(x >= left && x <= right && y >= top && y <= bot){
        DescriptionManager::get_description()->set_text(sdl_panel->get_building_information().description);
    } else {
        DescriptionManager::get_description()->set_text("");
    }


}