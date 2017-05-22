#ifndef CONSTRUCT_AND_DESTROY_PLAYER_H
#define CONSTRUCT_AND_DESTROY_PLAYER_H

#include <vector>
#include "types.h"
#include "resources.h"
#include "entity/static/building/building_entity.h"

class MovingEntityFactory;
class BuildingEntity;

class StaticEntity;

class MovingEntity;

template<class T>
class StateMachine;

class Player {

private:
    int _id;
public:
    Player(int);

    Resources *resources;
    std::vector<BuildingEntity *> buildings;
    std::vector<MovingEntity *> units;
    std::vector<MovingEntity *> selected_units;
    StateMachine<Player> *state_machine;
    BuildingEntity *positioning_building = nullptr;
    BuildingEntity* selected_building;


    void update();

    virtual ~Player();

    void select_units_in_rectangle(float start_x, float start_y, float end_x, float end_y);

    void select_one_unit(vec2 pos);
    void select_building(vec2 pos);

    void clear_all_selections();
    int get_id();

    void remove_unit(BaseEntity*);


};


#endif //CONSTRUCT_AND_DESTROY_PLAYER_H
