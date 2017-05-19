//
// Created by Stephan Schrijver on 1-5-2017.
//

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
}