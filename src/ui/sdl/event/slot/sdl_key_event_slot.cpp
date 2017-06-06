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

SDL_KeyEventSlot::SDL_KeyEventSlot() : Slot<sdl_key_event_data>() {}

void SDL_KeyEventSlot::on(sdl_key_event_data d) {
    // Get  player
    // TODO: Resolve correct player id
    Player *p = PlayerManager::get_instance()->get_player(player_id);

    // On ESC
    if (d.key == 27) {
        // If the current player state is ChoosingBuildingPosition then abort
        if (dynamic_cast<const ChoosingBuildingPosition *>(p->state_machine->current_state) != 0) {
            p->state_machine->change_state(new AbortPlacingBuilding());
        }
    }

    Player *player = PlayerManager::get_instance()->get_player(player_id);
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

