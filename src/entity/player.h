#ifndef CONSTRUCT_AND_DESTROY_PLAYER_H
#define CONSTRUCT_AND_DESTROY_PLAYER_H

#include <vector>
#include "resources.h"
#include "static/static_entity.h"
#include "moving/moving_entity.h"

class Player {
public:
    Player();
    virtual ~Player();

    Resources resources;
    std::vector<StaticEntity *> buildings;
    std::vector<MovingEntity *> units;
    std::vector<MovingEntity *> selected_units;
};


#endif //CONSTRUCT_AND_DESTROY_PLAYER_H
