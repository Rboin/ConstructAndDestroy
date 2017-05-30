//
// Created by Stephan on 18-04-2017.
//

#include <iostream>
#include "building_entity.h"
#include "building_manager.h"
#include "entity/moving/moving_entity_manager.h"
#include "entity/resources.h"

BuildingEntity::BuildingEntity(const mesh *base, vec2 position, float mass, BuildingType bt, TextureTypes texture_types)
        : StaticEntity(base,
                       position,
                       mass) {
    building_type = bt;
    costs = new Resources(0, 0, 0, 0);
    order_time = 10000;
    spawn = this->_position;
    spawn.y += 40;
    delta_time = 0;
    _health = 1000;
    _max_health = 1000;
}

BuildingEntity::BuildingEntity(const mesh *base, float mass, BuildingType bt, TextureTypes texture_types)
        : StaticEntity(base,
                       mass) {
    building_type = bt;
    costs = new Resources(0, 0, 0, 0);
    order_time = 10000;
    spawn = this->_position;
    spawn.y += 40;
    delta_time = 0;
    _health = 1000;
    _max_health = 1000;
}

Resources *BuildingEntity::get_costs() {
    return costs;
}

BuildingType BuildingEntity::get_building_type() {
    return building_type;
}

void BuildingEntity::update(float d) {
    if(!this->orders.empty()){

        delta_time += d;

        if(delta_time >= order_time){

            this->order_unit_from_factory(_player, spawn, orders.front());

            //remove first from orders.
            orders.erase(orders.begin());
            spawn.y += 40;
            //reset order time.
            delta_time = 0;
        }
    };
}

void BuildingEntity::order_unit_from_factory(Player *player, vec2 position, MovingEntityType moving_entity_type) {
    MovingEntityManager::get_instance()->add_unit(player, position, moving_entity_type);
}

void BuildingEntity::order_unit(MovingEntityType moving_entity_type) {
    this->orders.push_back(moving_entity_type);
}

std::vector<SpawnableEntity*> BuildingEntity::get_spawnable_entities() {
    return spawnable_entities;
}

BuildingEntity::~BuildingEntity() {
    for(int i = 0; i < spawnable_entities.size(); i++) {
        delete spawnable_entities.at(i);
    }
}

void BuildingEntity::set_position(float x, float y, bool finalposition) {
    StaticEntity::set_position(x, y, finalposition);

    spawn = this->_position;
    spawn.y += 40;
}

int BuildingEntity::get_order_time() {
    return order_time;
}
