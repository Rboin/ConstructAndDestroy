
#ifndef CONSTRUCT_AND_DESTROY_MOVING_ENTITY_FACTORY_H
#define CONSTRUCT_AND_DESTROY_MOVING_ENTITY_FACTORY_H

#include "vector.h"
#include "moving_entity_types.h"

class Player;
class MovingEntity;

class MovingEntityFactory {
public:
    static MovingEntity* create(Player* player,vec2 position, MovingEntityType moving_entity_type);
    ~MovingEntityFactory();
};

#endif //CONSTRUCT_AND_DESTROY_MOVING_ENTITY_FACTORY_H