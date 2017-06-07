//
// Created by Stephan Schrijver on 1-5-2017.
//

#include <vector>
#include <iostream>
#include "sdl/panel/sdl_world_panel.h"
#include "sdl/panel/sdl_entity_panel.h"
#include "sdl/event/sdl_event_types.h"
#include "manager/build_and_spawn_manager.h"
#include "sdl/panel/sdl_control_panel.h"
#include "entity/moving/spawnable_entity.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "state/state_machine.h"
#include "entity/static/building/building_state/choosing_building_position.h"
#include "entity/static/building/building_state/placing_building.h"
#include "entity/static/building/building_state/abort_placing_building.h"
#include "sdl_key_event_slot.h"
#include "settings.h"
#include "entity/static/building/building_manager.h"

SDL_KeyEventSlot::SDL_KeyEventSlot() : Slot<sdl_key_event_data>() {
    this->_building_index = -1;
}

void SDL_KeyEventSlot::on(sdl_key_event_data d) {

    if(d.type != SDL_KEYUP)
    {
        // ONLY HANDLE KEY UP EVENTS
        return;
    }
    // Get  player
    // TODO: Resolve correct player id
    Player *player = PlayerManager::get_instance()->get_player(player_id);

    // On ESC
    if (d.key == 27) {
        // If the current player state is ChoosingBuildingPosition then abort
        if (dynamic_cast<const ChoosingBuildingPosition *>(player->state_machine->current_state) != 0) {
            player->state_machine->change_state(new AbortPlacingBuilding());
            return;
        }
    }

    if (d.key == 9 && d.type == SDL_KEYUP) {
        handle_tab(player);
        return;
    }


    try {
        if (player->selected_building != nullptr) {
            // _key_event_handler_entity:
            BuildingEntity *selected_building = player->selected_building;
            std::vector<SpawnableEntity *> se = selected_building->get_spawnable_entities();


            int key = (int) d.key - 49;
            if (key < se.size() && key >= 0) {
                SDLUnitPanel *panel = (SDLUnitPanel *) SDLControlPanel::get_instance()->get_children()[0]->get_children()[key];
                BuildAndSpawnManager::get_instance()->spawn_spawnable_entity(panel);
            }

        } else {
            int key = (int) d.key - 49;
            if (key < buildings_with_textures.size() && key >= 0) {
                SDLUnitPanel *panel = (SDLUnitPanel *) SDLControlPanel::get_instance()->get_children()[0]->get_children()[key];
                BuildAndSpawnManager::get_instance()->build_building(panel);
            }
        }
    } catch (int e) {
        std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }
}

void SDL_KeyEventSlot::handle_tab(Player *player) {

    if (player->selected_building != nullptr) {
        player->selected_building->deselect();
    }

    this->_building_index++;
    if (this->_building_index == player->buildings.size()) {
        this->_building_index = 0;
    }

    if (player->selected_building == player->buildings[this->_building_index]) {
        //the currently selected building is the same as found at the building index.
        //So this method is called again so it will select the next building instead.
        handle_tab(player);
    } else {
        player->buildings[this->_building_index]->select();
        player->selected_building = player->buildings[this->_building_index];
    }
}