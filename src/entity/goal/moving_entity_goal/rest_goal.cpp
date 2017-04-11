//
// Created by Sander on 4-4-2017.
//

#include "rest_goal.h"
#include <entity/static/resource_manager.h>
#include <entity/goal/moving_entity_goal/atomic/plan_path_goal.h>
#include <graph/graph_manager.h>
#include <graph/graph.h>
#include <entity/goal/moving_entity_goal/atomic/sleep_goal.h>
#include "strategy_goal_type.h"
#include "follow_path_goal.h"
#include "entity/moving/moving_entity.h"

RestGoal::RestGoal(MovingEntity *e) : GoalComposite(e, REST) {
    set_goal_plan_path_to_campfire();
    set_goal_follow_path();
    set_goal_sleep();
}

void RestGoal::determine_next_goal() {
    if (this->sub_goals.size() == 0) {
        status = COMPLETED;
    }
}

void RestGoal::set_goal_plan_path_to_campfire() {
    GraphManager *gm = GraphManager::get_instance();
    int start = gm->graph->get_node_with_position(owner->get_position());
    this->sub_goals.push_front(new PlanPathGoal(owner, gm->graph->nodes[start], find_campfire_node()));
}

void RestGoal::set_goal_follow_path() {
    this->sub_goals.push_front(new FollowPathGoal(owner));
}

void RestGoal::set_goal_sleep() {
    this->sub_goals.push_front(new SleepGoal(owner));
}

void RestGoal::activate() {
    status = ACTIVE;
}

const int RestGoal::process() {
    activate_if_inactive();
    determine_next_goal();
    return process_subgoals();
}

void RestGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

Node *RestGoal::find_campfire_node() {
    ResourceManager *rm = ResourceManager::get_instance();

    vec2 campfire_position = rm->get_closest_resource(owner->get_position(), CAMPFIRE);

    GraphManager *gm = GraphManager::get_instance();
    int index = gm->graph->get_node_with_position(campfire_position);
    Node *goal = gm->graph->nodes.at(index);

    return goal;
}

const char *RestGoal::get_name() const {
    return "Rest";
}

