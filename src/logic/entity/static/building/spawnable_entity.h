//
// Created by Jeroen on 5/18/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_H
#define CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_H

class Resources;
#include "entity/moving/moving_entity_types.h"

class SpawnableEntity {
private:
    Resources* _cost;
    MovingEntityType _entity_type;
public:
    SpawnableEntity(Resources* cost, MovingEntityType entityType);

    ~SpawnableEntity();

    SpawnableEntity(Resources* cost);

    Resources* get_cost();

    MovingEntityType get_entity_type();
};


#endif //CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_H
