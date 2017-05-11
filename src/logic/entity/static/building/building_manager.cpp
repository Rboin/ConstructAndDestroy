//
// Created by Stephan on 18-04-2017.
//

#include "building_manager.h"
#include "entity/static/building/building_state/choosing_building_position.h"
#include "entity/static/building/building_state/placing_building.h"
#include "world/world.h"
#include "entity/player_manager.h"
#include "castle_entity.h"
#include "building_factory.h"
#include "entity/player.h"
#include "entity/state/state_machine.h"

BuildingManager *BuildingManager::instance = nullptr;

BuildingManager::BuildingManager() {
}

BuildingManager::~BuildingManager() {
    if (buildings.size() > 0) {
        for (int i = 0; i < buildings.size(); i++) {
            delete buildings.at(i);
        }
    }
}

BuildingManager *BuildingManager::get_instance() {
    if (!instance)
        instance = new BuildingManager();
    return instance;
}

void BuildingManager::choose_building_position(int player_id, std::string type) {
    BuildingEntity *be = BuildingFactory::create(type);

    // Add building to the world (so it will be rendered)
    World::get_instance()->add_entity(be);

    Player* player = PlayerManager::get_instance()->get_player(player_id);

    // Change state of player to ChoosingBuildingPosition
    player->positioning_object = be;
    player->state_machine->change_state(new ChoosingBuildingPosition());


}

void BuildingManager::add_building(Player* p, BuildingEntity *be) {
    // Add building to building array kept by the BuildingManager
    buildings.emplace_back(be);

    // Add building to the player
    p->buildings.push_back(p->positioning_object);
}

std::vector<BuildingEntity *> BuildingManager::get_buildings() {
    return buildings;
}

void BuildingManager::remove_building(Player * p, BuildingEntity *be) {

    // Remove building entity from world so it will not be drawn anymore
    World::get_instance()->remove_entity(p->positioning_object);
    
    // Delete building from the building array kept by the BuildingManager
    for (std::vector<BuildingEntity *>::iterator iter = buildings.begin(); iter != buildings.end(); ++iter) {
        if (*iter == be) {
            buildings.erase(iter);
            break;
        }
    }

    // Delete building from the building array kept by the player
    for (std::vector<BuildingEntity *>::iterator iter = p->buildings.begin(); iter != p->buildings.end(); ++iter) {
        if (*iter == be) {
            p->buildings.erase(iter);
            break;
        }
    }

    // afterwards: safely delete the building
    delete p->positioning_object;
    p->positioning_object = nullptr;
}