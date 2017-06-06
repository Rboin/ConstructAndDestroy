//
// Created by Stephan Schrijver on 29-5-2017.
//

#include "entity/static/building/building_manager.h"
#include "state/state_machine.h"
#include "entity/player.h"
#include "entity/player_manager.h"
#include "entity/static/building/building_state/choosing_building_position.h"
#include "entity/moving/spawnable_entity_manager.h"
#include "build_and_spawn_manager.h"
#include "sdl/panel/sdl_unit_panel.h"

BuildAndSpawnManager *BuildAndSpawnManager::_instance = nullptr;

BuildAndSpawnManager *BuildAndSpawnManager::get_instance() {
    if (_instance == nullptr) {
        _instance = new BuildAndSpawnManager();
    }
    return _instance;
}

void BuildAndSpawnManager::spawn_spawnable_entity(SDLUnitPanel *sdl_panel) {
    BuildingEntity *building = sdl_panel->get_building_entity();
    SpawnableEntity *spawnable_entity = sdl_panel->get_spawnable_entity();

    SpawnableEntityManager::get_instance()->spawn_entity(building, spawnable_entity);
}

BuildAndSpawnManager::~BuildAndSpawnManager() {
    _instance = nullptr;
}

void BuildAndSpawnManager::build_building(SDLUnitPanel * sdl_panel) {
    Player *p = PlayerManager::get_instance()->get_player(player_id);

    // If current state of an user is NOT ChoosingBuildingPosition,
    // then let it position a building
    // If it is positioning a building, the user has found a position so change
    // the state to PlacingBuilding
    if (dynamic_cast<const ChoosingBuildingPosition *>(p->state_machine->current_state) == 0) {
        BuildingManager::get_instance()->choose_building_position(player_id, sdl_panel->get_building_type());
    }
}
