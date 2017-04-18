//
// Created by Sander on 23-3-2017.
//

#include <vector.h>
#include <neighbourhood_manager.h>
#include <entity/entity_types.h>
#include "mouse_handler.h"
#include "graph/graph.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

bool MouseHandler::handle(mouse_event_data data) {
    vec2 pos = {(float) data.data.x, (float) data.data.y};

    switch(data.data.button) {
        case SDL_BUTTON_LEFT:
            return handle_left_button(pos);
        case SDL_BUTTON_RIGHT:
            return handle_right_button(data, pos);
        default:
            return false;
    }
}

const bool MouseHandler::handle_left_button(const vec2 &v) {
    bool result = false;
    BaseEntity *selected = NeighbourhoodManager::get_instance()->get_closest_to(v);
    if(selected && selected->is(EntityType::MOVING)) {
        o_data = (MovingEntity *) selected;
        result = true;
    } else
        o_data = nullptr;

    this->notify();
    return result;
}

const bool MouseHandler::handle_right_button(mouse_event_data &data, const vec2 &v) {
    int goal = data.graph->get_node_with_position(v);
    int start = data.graph->get_node_with_position(data.cc->get_position());

    std::vector<vec2 *> path = data.graph->a_star_path(data.graph->nodes[start], data.graph->nodes[goal]);
    data.graph->draw_path.clear();
    data.graph->draw_path = path;
    data.cc->path = path;
    data.cc->get_brain()->set_goal_follow_path();
}
