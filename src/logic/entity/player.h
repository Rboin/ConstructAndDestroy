#ifndef CONSTRUCT_AND_DESTROY_PLAYER_H
#define CONSTRUCT_AND_DESTROY_PLAYER_H

#include <vector>
#include "resources.h"

class BuildingEntity;
class StaticEntity;
class MovingEntity;

template<class T> class StateMachine;

class Player {
public:
    Player();
    Resources resources;
    std::vector<BuildingEntity *> buildings;
    std::vector<MovingEntity *> units;
    std::vector<MovingEntity *> selected_units;
    StateMachine<Player>* state_machine;
    BuildingEntity* positioning_object = nullptr;

    void update();
    virtual ~Player();

    void select_units_in_rectangle(float start_x, float start_y, float end_x, float end_y);

    void clear_selected_units();
};


#endif //CONSTRUCT_AND_DESTROY_PLAYER_H
