#ifndef CONSTRUCT_AND_DESTROY_MOVING_ENTITY_MANAGER_H
#define CONSTRUCT_AND_DESTROY_MOVING_ENTITY_MANAGER_H

#include "vector.h"
#include "moving_entity_types.h"

class Player;


class MovingEntityManager {
private:
    MovingEntityManager();

    static MovingEntityManager *instance;

public:
    ~MovingEntityManager();

    static MovingEntityManager *get_instance();

    void add_unit(Player *player, vec2 position, MovingEntityType moving_entity_type, float stat_modifier = 1.0f);

};



#endif //CONSTRUCT_AND_DESTROY_MOVING_ENTITY_MANAGER_H
