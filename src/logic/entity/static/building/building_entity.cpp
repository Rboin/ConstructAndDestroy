//
// Created by Stephan on 18-04-2017.
//

#include <iostream>
#include "building_entity.h"
#include "building_manager.h"
#include "entity/moving/moving_entity_manager.h"
#include "entity/resources.h"
#include "entity/moving/spawnable_entity.h"

BuildingEntity::BuildingEntity(vec2 position, float mass, BuildingType bt, TextureTypes texture_types)
        : StaticEntity(position,
                       mass) {
    _building_type = bt;
    costs = new Resources(0, 0, 0, 0);
    _order_time = 10000;
    _delta_time = 0;
    _health = 1000;
    _max_health = 1000;
}

BuildingEntity::BuildingEntity(float mass, BuildingType bt, TextureTypes texture_types)
        : StaticEntity(mass) {
    _building_type = bt;
    costs = new Resources(0, 0, 0, 0);
    _order_time = 10000;
    _delta_time = 0;
    _health = 1000;
    _max_health = 1000;
}

Resources *BuildingEntity::get_costs() {
    return costs;
}

BuildingType BuildingEntity::get_building_type() {
    return _building_type;
}

void BuildingEntity::update(float d) {
    if (!this->_orders.empty()) {

        _delta_time += d;

        if (_delta_time >= _order_time) {

            this->order_unit_from_factory(_player, {this->get_position().x, this->get_position().y + 40}, _orders.front());

            //remove first from orders.
            _orders.erase(_orders.begin());

            //reset order time.
            _delta_time = 0;
        }
    };
}

void BuildingEntity::order_unit_from_factory(Player *player, vec2 position, MovingEntityType moving_entity_type) {
    MovingEntityManager::get_instance()->add_unit(player, position, moving_entity_type);
}

void BuildingEntity::order_unit(MovingEntityType moving_entity_type) {
    this->_orders.push_back(moving_entity_type);
}

std::vector<SpawnableEntity *> BuildingEntity::get_spawnable_entities() {
    return spawnable_entities;
}

BuildingEntity::~BuildingEntity() {
    for (int i = 0; i < spawnable_entities.size(); i++) {
        delete spawnable_entities.at(i);
    }
    delete costs;
}

int BuildingEntity::get_order_time() {
    return _order_time;
}

int BuildingEntity::get_delta_time() {
    return _delta_time;
}

std::vector<MovingEntityType> BuildingEntity::get_orders() {
    return _orders;
}

std::vector<Upgrade *> BuildingEntity::get_upgrades() {
    return upgrades;
}
