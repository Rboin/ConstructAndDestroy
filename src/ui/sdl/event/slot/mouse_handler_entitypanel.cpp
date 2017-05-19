//
// Created by Jeroen on 5/18/2017.
//

#include "mouse_handler_entitypanel.h"
#include <entity/player_manager.h>
#include <entity/static/building/building_state/choosing_building_position.h>
#include <entity/static/building/building_state/placing_building.h>
#include <entity/static/building/building_manager.h>
#include "mouse_handler_buildingpanel.h"
#include "world/world.h"
#include "entity/player.h"
#include "settings.h"
#include "state/state_machine.h"

MouseHandlerEntityPanel::MouseHandlerEntityPanel() {
}

MouseHandlerEntityPanel::~MouseHandlerEntityPanel() {}

void MouseHandlerEntityPanel::handle_up(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    Player *p = PlayerManager::get_instance()->get_player(player_id);

    BuildingEntity* building = sdl_panel->get_building_entity();

    if (p->resources->check_if_sufficient_resources(building->get_costs())) {
        SpawnableEntity* spawnable_entity = sdl_panel->get_spawnable_entity();

        building->order_unit(spawnable_entity->get_entity_type());

        p->resources->subtract_resources(spawnable_entity->get_cost());
    }
}


void MouseHandlerEntityPanel::on(sdl_mouse_event_data data) {
    SDLUnitPanel *sdl_panel = (SDLUnitPanel *) data.component;
    if( data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP){
        handle(data, sdl_panel);
    }
}

void MouseHandlerEntityPanel::handle(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
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