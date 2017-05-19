//
// Created by Jeroen on 5/18/2017.
//

#include <entity/resources.h>
#include "spawnable_entity.h"

SpawnableEntity::SpawnableEntity(Resources* cost, MovingEntityType entityType) {
    this->cost = cost;
    this->entityType = entityType;
}

Resources *SpawnableEntity::get_cost() {
    return this->cost;
}

MovingEntityType SpawnableEntity::get_entity_type() {
    return this->entityType;
}
