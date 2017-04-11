//
// Created by Sander on 2-3-2017.
//

#ifndef C_AND_D_PROJECT_EXPLORE_STRATEGY_H
#define C_AND_D_PROJECT_EXPLORE_STRATEGY_H

#include "behaviour_strategy.h"
#include <vector>
#include "types.h"

class Graph;

class Node;

enum Moving {
    up_left, up_right, left, right, down_left, down_right, start_pos
};

class ExploreStrategy : public BehaviourStrategy {
private:
    int pos_in_g;
    int starting_pos;
    Graph *graph;
    bool is_moving;
    bool reached_top;
    bool explored_map;
    bool graph_generated;
    Moving moving_to;

public:
    ExploreStrategy();

    vec2 calculate_force(MovingEntity &, std::vector<BaseEntity *>);

    void generate_path(MovingEntity &);

    void move_up();

    void move_down();

    void check_distance(MovingEntity &);

    void starting_position();
};

#endif //C_AND_D_PROJECT_EXPLORE_STRATEGY_H
