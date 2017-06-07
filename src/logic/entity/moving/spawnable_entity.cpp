//
// Created by Jeroen on 5/18/2017.
//

#include <string>
#include "entity/resources.h"
#include "spawnable_entity.h"


SpawnableEntity::SpawnableEntity(Resources* cost, MovingEntityType entity_type) {
    this->_cost = cost;
    this->_entity_type = entity_type;
}

SpawnableEntity::SpawnableEntity(Resources *cost, MovingEntityType entity_type, std::string description) {
    this->_cost = cost;
    this->_entity_type = entity_type;
    this->_description = description;
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

std::string SpawnableEntity::get_name() {
    std::string name = "unit";
    switch(this->_entity_type){
        case MovingEntityType::LUMBERJACK:
            name = "Lumberjack";
            break;
        case MovingEntityType::MINER:
            name = "Miner";
            break;
        case MovingEntityType::KNIGHT:
            name = "Knight";
            break;
        case  MovingEntityType::CAVALIER:
            name = "Cavalier";
            break;
        case MovingEntityType::HEAVY_CAVALIER:
            name = "Heavy Cavalier";
            break;
        case MovingEntityType::LIGHT_CAVALIER:
            name = "Light Cavalier";
            break;
        case MovingEntityType::JUGGERNAUT:
            name = "Juggernaut";
            break;
        case MovingEntityType::MERCENARY:
            name = "Mercenary";
            break;
    }

    return name;
}

std::string SpawnableEntity::get_description() {
    return this->_description;
}

