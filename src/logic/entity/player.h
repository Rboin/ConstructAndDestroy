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
class KnightEntity;

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

    void clear_selected_building(BaseEntity* be);

    void clear_selected_entity(BaseEntity *be);

    void remove_entity(BaseEntity*);

    void remove_unit(MovingEntity*);

    void remove_building(BuildingEntity*);

    void clear_buildings();

    void clear_units();

    MovingEntity* get_combat_unit();

    void reset();
};


#endif //CONSTRUCT_AND_DESTROY_PLAYER_H
