//
// Created by Stephan Schrijver on 29-5-2017.
//

#include "settings.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "spawnable_entity_manager.h"
#include "spawnable_entity.h"

SpawnableEntityManager *SpawnableEntityManager::_instance = nullptr;

SpawnableEntityManager::SpawnableEntityManager() {}

SpawnableEntityManager *SpawnableEntityManager::get_instance() {
    if (_instance == nullptr) {
        _instance = new SpawnableEntityManager();
    }
    return _instance;
}

bool SpawnableEntityManager::spawn_entity(BuildingEntity *building, SpawnableEntity *spawnable_entity) {
    Player *p = PlayerManager::get_instance()->get_player(player_id);

    if (p->resources->check_if_sufficient_resources(spawnable_entity->get_cost())) {
        // tell the building to spawn the selected entity type
        building->order_unit(spawnable_entity->get_entity_type());

        // remove resources from the player
        p->resources->subtract_resources(spawnable_entity->get_cost());
        return true;
    }
    return false;
}