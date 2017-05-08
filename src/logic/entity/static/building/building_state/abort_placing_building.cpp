//
// Created by Stephan Schrijver on 2-5-2017.
//

#include <entity/player_manager.h>
#include <entity/static/building/building_manager.h>
#include <world/world.h>
#include "abort_placing_building.h"
#include "entity/static/building/building_entity.h"
#include "entity/state/state_machine.h"
#include "entity/player.h"

void AbortPlacingBuilding::enter(Player *p) {
    BuildingManager::get_instance()->remove_building(p, p->positioning_object);

}

void AbortPlacingBuilding::execute(Player *p) {
    p->state_machine->clear_state();
}


void AbortPlacingBuilding::exit(Player *p) {
    // Nothing to do!
}
