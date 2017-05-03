#ifndef CONSTRUCT_AND_DESTROY_PLAYER_H
#define CONSTRUCT_AND_DESTROY_PLAYER_H

#include <vector>
#include "resources.h"

class StaticEntity;
class MovingEntity;

class Player {
public:

    Resources resources;
    std::vector<StaticEntity *> buildings;
    std::vector<MovingEntity *> units;
    std::vector<MovingEntity *> selected_units;

    Player();
    virtual ~Player();

    void select_units_in_rectangle(float start_x, float start_y, float end_x, float end_y);

    void clear_selected_units();

};


#endif //CONSTRUCT_AND_DESTROY_PLAYER_H
