//
// Created by Stephan Schrijver on 29-5-2017.
//

#include "entity/moving/spawnable_entity_manager.h"
#include "build_and_spawn_manager.h"
#include "sdl/progressbar/sdl_progressbar_render_object.h"
#include "sdl/panel/sdl_progressbar_panel.h"
#include "sdl/panel/sdl_unit_panel.h"
#include "entity/static/building/building_entity.h"

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
