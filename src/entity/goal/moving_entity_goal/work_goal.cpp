//
// Created by Sander on 19-3-2017.
//

#include <entity/static/resource_manager.h>
#include <entity/goal/moving_entity_goal/atomic/plan_path_goal.h>
#include <graph/graph_manager.h>
#include <graph/graph.h>
#include <goal/composite_goal.h>
#include <entity/goal/moving_entity_goal/atomic/gather_resource_goal.h>
#include <entity/goal/moving_entity_goal/atomic/drop_resources_goal.h>
#include "work_goal.h"
#include "strategy_goal_type.h"
#include "follow_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "job_type.h"

WorkGoal::WorkGoal(MovingEntity *e) : GoalComposite(e, WORK) {
    set_goal_plan_path_to_resource();
    set_goal_follow_path();
    set_goal_gather_resource();
    set_goal_plan_path_home();
    set_goal_follow_path();
    set_goal_drop_resources();
}

void WorkGoal::add_evaluator(GoalEvaluator<MovingEntity> *e) {
    _evaluators.push_back(e);
}

void WorkGoal::determine_next_goal() {
    if (this->sub_goals.size() == 0) {
        status = COMPLETED;
    }
}

void WorkGoal::set_goal_plan_path_to_resource() {
    GraphManager *gm = GraphManager::get_instance();
    int start = gm->graph->get_node_with_position(owner->get_position());

    resource = find_resource_node();
    this->sub_goals.push_front(new PlanPathGoal(owner, gm->graph->nodes[start], resource));
    resource = gm->graph->nodes[resource->get_index() - 1];
}

void WorkGoal::set_goal_plan_path_home() {

    this->sub_goals.push_front(new PlanPathGoal(owner, find_closest_edge(), find_home_node()));
}

void WorkGoal::set_goal_follow_path() {
    this->sub_goals.push_front(new FollowPathGoal(owner));
}


void WorkGoal::activate() {
    status = ACTIVE;
}

const int WorkGoal::process() {
    activate_if_inactive();
    determine_next_goal();
    return process_subgoals();
}

void WorkGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

Node *WorkGoal::find_resource_node() {
    ResourceManager *rm = ResourceManager::get_instance();
    ResourceType rt;
    if (owner->job_type == WOODCUTTER) {
        rt = TREE;
    }
    if (owner->job_type == MINER) {
        rt = IRONMINE;
    }
    vec2 resource_position = rm->get_closest_resource(owner->get_position(), rt);

    GraphManager *gm = GraphManager::get_instance();
    int index = gm->graph->get_node_with_position(resource_position);
    Node *goal = gm->graph->nodes.at(index);

    return goal;
}

Node *WorkGoal::find_home_node() {
    GraphManager *gm = GraphManager::get_instance();
    ResourceManager *rm = ResourceManager::get_instance();

    vec2 warehouse_position = rm->get_closest_resource(owner->get_position(), WAREHOUSE);
    int index = gm->graph->get_node_with_position(warehouse_position);
    Node *goal = gm->graph->nodes.at(index);

    return goal;
}

void WorkGoal::set_goal_gather_resource() {
    this->sub_goals.push_front(new GatherResourceGoal(owner));
}

void WorkGoal::set_goal_drop_resources() {
    this->sub_goals.push_front(new DropResourcesGoal(owner));
}

const char *WorkGoal::get_name() const {
    return "Work";
}

Node *WorkGoal::find_closest_edge() {
    if (resource->get_neighbors().size() == 0) {
        GraphManager *gm = GraphManager::get_instance();
        for (int i = resource->get_index(); i < 300; i++) {
            if (gm->graph->nodes[i]->get_neighbors().size() != 0) {
                return gm->graph->nodes[i];
            }
        }
    } else {
        return resource;
    }
}
