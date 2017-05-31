//
// Created by Jeroen on 5/18/2017.
//

#include "entity/resources.h"
#include "spawnable_entity.h"

SpawnableEntity::SpawnableEntity(Resources* cost, MovingEntityType entityType) {
    this->_cost = cost;
    this->_entity_type = entityType;
}

SpawnableEntity::~SpawnableEntity() {
    delete _cost;
}

Resources *SpawnableEntity::get_cost() {
    return this->_cost;
}

MovingEntityType SpawnableEntity::get_entity_type() {
    return this->_entity_type;
}
