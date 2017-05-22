//
// Created by Jeroen on 5/11/2017.
//

#include "sdl/panel/sdl_unit_panel.h"
#include "entity/player_manager.h"
#include "entity/static/building/building_state/choosing_building_position.h"
#include "entity/static/building/building_state/placing_building.h"
#include "entity/static/building/building_manager.h"
#include "mouse_handler_buildingpanel.h"
#include "world/world.h"
#include "entity/player.h"
#include "settings.h"
#include "state/state_machine.h"

MouseHandlerBuildingPanel::MouseHandlerBuildingPanel() {
}

MouseHandlerBuildingPanel::~MouseHandlerBuildingPanel() {}

void MouseHandlerBuildingPanel::handle_up(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    Player *p = PlayerManager::get_instance()->get_player(player_id);

    // If current state of an user is NOT ChoosingBuildingPosition,
    // then let it position a building
    // If it is positioning a building, the user has found a position so change
    // the state to PlacingBuilding
    if (dynamic_cast<const ChoosingBuildingPosition *>(p->state_machine->current_state) == 0) {
        BuildingManager::get_instance()->choose_building_position(player_id, sdl_panel->get_building_type());
    }
}


void MouseHandlerBuildingPanel::on(sdl_mouse_event_data data) {
    SDLUnitPanel *sdl_panel = (SDLUnitPanel *) data.component;
    if( data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP){
        handle(data, sdl_panel);
    }
}

void MouseHandlerBuildingPanel::handle(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    vec2 pos = data.position;

    switch(data.button) {
        case SDL_BUTTON_LEFT:
            if (data.type == SDL_MOUSEBUTTONUP) {
                return handle_up(data, sdl_panel);
            }

            return;

        default:
            return;
    }
}