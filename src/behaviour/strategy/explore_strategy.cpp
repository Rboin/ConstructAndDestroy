//
// Created by Sander on 2-3-2017.
//

#include <cmath>
#include <graph/graph_manager.h>
#include "explore_strategy.h"
#include "entity/moving/moving_entity.h"
#include "graph/graph.h"

ExploreStrategy::ExploreStrategy() {
    GraphManager *gm = GraphManager::get_instance();
    graph = gm->graph;
    is_moving = false;
    reached_top = false;
    explored_map = false;
    graph_generated = false;
    moving_to = left;
}

vec2 ExploreStrategy::calculate_force(MovingEntity &e, std::vector<BaseEntity *> neighbourhood) {
    if (!explored_map) {
        if (!graph_generated) {
            generate_path(e);
            starting_position();
        }

        check_distance(e);

        if (!is_moving) {
            if (!reached_top) {
                move_up();
            } else if (reached_top) {
                move_down();
            }
        }
    }

    return ((*_targets - e.get_position()).normalize() * e.get_max_speed()) - e.get_velocity();
}

void ExploreStrategy::generate_path(MovingEntity &e) {
    vec2 entity_position = e.get_position();
    for (int i = 0; i < graph->nodes.size(); i++) {
        vec2 *position_in_graph = graph->nodes[i]->get_position();
        if (entity_position.x - position_in_graph->x <= 40 && entity_position.y - position_in_graph->y <= 40) {
            starting_pos = i;
            pos_in_g = i;
            break;
        }
    }
    graph_generated = true;
}

void ExploreStrategy::move_up() {
//move up on the left
    if (moving_to == left) {
        pos_in_g -= 40;
        moving_to = up_left;
    }
        //move up on the right
    else if (moving_to == right) {
        pos_in_g -= 40;
        moving_to = up_right;
    }
        //move to the right
    else if (moving_to == up_left) {
        pos_in_g += 14;
        moving_to = right;
    }
        //move to the left
    else if (moving_to == up_right) {
        pos_in_g -= 14;
        moving_to = left;
    }
    if (graph->nodes[pos_in_g]->get_position()->y < 41) {
        reached_top = true;
        pos_in_g = starting_pos;
        moving_to = start_pos;
    }
    is_moving = true;
    _targets = graph->nodes[pos_in_g]->get_position();
}

void ExploreStrategy::move_down() {
    if (moving_to == start_pos) {
        while ((pos_in_g + 3) % 20 != 0) {
            pos_in_g++;
        }
        moving_to = right;
    } else if (moving_to == left) {
        pos_in_g += 40;
        moving_to = down_left;
    }
        //move up on the right
    else if (moving_to == right) {
        pos_in_g += 40;
        moving_to = down_right;
    }
        //move to the right
    else if (moving_to == down_left) {
        pos_in_g += 14;
        moving_to = right;
    }
        //move to the left
    else if (moving_to == down_right) {
        pos_in_g -= 14;
        moving_to = left;
    }
    if (pos_in_g > graph->nodes.size()) {
        explored_map = true;
    } else {
        is_moving = true;
        _targets = graph->nodes[pos_in_g]->get_position();
    }
}

void ExploreStrategy::check_distance(MovingEntity &e) {
    float distance = e.get_position().distance_squared(*_targets);
    if (distance < 1) {
        is_moving = false;
    }
}

void ExploreStrategy::starting_position() {
    while ((pos_in_g - 3) % 20 != 0) {
        pos_in_g--;
    }
    //if the position in the graph is smaller then 0 set the target to 17 (right side in graph)
    if (starting_pos >= 0 && starting_pos < 17) {
        reached_top = true;
        moving_to = right;
        pos_in_g = 17;
    }

    _targets = graph->nodes[pos_in_g]->get_position();
    is_moving = true;
}

