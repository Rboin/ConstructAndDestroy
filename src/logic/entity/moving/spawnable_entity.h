//
// Created by Jeroen on 5/18/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_H
#define CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_H

#include "moving_entity_types.h"
#include <string>

class Resources;

class SpawnableEntity {
private:
    Resources* _cost;

    MovingEntityType _entity_type;
    std::string _description;
public:
    SpawnableEntity(Resources* cost, MovingEntityType entity_type);

    SpawnableEntity(Resources* cost, MovingEntityType entity_type, std::string description);

    ~SpawnableEntity();

    SpawnableEntity(Resources* cost);

    Resources* get_cost();

    MovingEntityType get_entity_type();

    std::string get_name();

    std::string get_description();
};


#endif //CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_H
