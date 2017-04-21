#ifndef CONSTRUCT_AND_DESTROY_PLAYER_H
#define CONSTRUCT_AND_DESTROY_PLAYER_H

#include <vector>
#include "resources.h"

class StaticEntity;
class MovingEntity;

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
