//
// Created by Sander on 4-4-2017.
//

#include "go_eat_goal.h"
#include "entity/static/resource_manager.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "graph/graph_manager.h"
#include "graph/graph.h"
#include "entity/goal/moving_entity_goal/atomic/eat_goal.h"
#include "entity/moving/moving_entity.h"
#include "strategy_goal_type.h"
#include "follow_path_goal.h"

GoEatGoal::GoEatGoal(MovingEntity *e) : GoalComposite(e, GOEAT) {
    set_goal_plan_path_to_restaurant();
    set_goal_follow_path();
    set_goal_eat();
}

void GoEatGoal::determine_next_goal() {
    if (this->sub_goals.size() == 0) {
        status = COMPLETED;
    }
}

void GoEatGoal::set_goal_plan_path_to_restaurant() {
    GraphManager *gm = GraphManager::get_instance();
    int start = gm->graph->get_node_with_position(owner->get_position());
    this->sub_goals.push_front(new PlanPathGoal(owner, gm->graph->nodes[start], find_restaurant_node()));
}

void GoEatGoal::set_goal_follow_path() {
    this->sub_goals.push_front(new FollowPathGoal(owner));
}

void GoEatGoal::set_goal_eat() {
    this->sub_goals.push_front(new EatGoal(owner));
}

void GoEatGoal::activate() {
    status = ACTIVE;
}

const int GoEatGoal::process() {
    activate_if_inactive();
    determine_next_goal();
    return process_subgoals();
}

void GoEatGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

Node *GoEatGoal::find_restaurant_node() {
    ResourceManager *rm = ResourceManager::get_instance();

    vec2 campfire_position = rm->get_closest_resource(owner->get_position(), RESTAURANT);

    GraphManager *gm = GraphManager::get_instance();
    int index = gm->graph->get_node_with_position(campfire_position);
    Node *goal = gm->graph->nodes.at(index);

    return goal;
}

const char *GoEatGoal::get_name() const {
    return "GoEat";
}
