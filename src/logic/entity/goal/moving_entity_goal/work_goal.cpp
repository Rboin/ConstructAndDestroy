//
// Created by Sander on 19-3-2017.
//

#include "goal/composite_goal.h"
#include <iostream>
#include "entity/static/resource_manager.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "graph/graph_manager.h"
#include "graph/graph.h"
#include "entity/goal/moving_entity_goal/atomic/gather_resource_goal.h"
#include "entity/goal/moving_entity_goal/atomic/drop_resources_goal.h"
#include "entity/moving/moving_entity.h"
#include "work_goal.h"
#include "types.h"
#include "strategy_goal_type.h"
#include "follow_path_goal.h"
#include "job_type.h"

WorkGoal::WorkGoal(MovingEntity *e, vec2* target_resource, int initiator) : GoalComposite(e, WORK, initiator) {
    _target_resource = target_resource;
    set_goal_plan_path_to_resource();
    if (resource->get_index() != 0) {
        set_goal_follow_path();
        set_goal_gather_resource();
        set_goal_plan_path_home();
        set_goal_follow_path();
        set_goal_drop_resources();
    }
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
    if (resource->get_index() != 0) {
        this->sub_goals.push_front(new PlanPathGoal(owner, gm->graph->find_closest_edge(resource)));
    }
}

void WorkGoal::set_goal_plan_path_home() {
    this->sub_goals.push_front(new PlanPathGoal(owner, find_depot()));
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
    if (owner->job_type == WOODCUTTER) {
        rt = TREE;
    }
    if (owner->job_type == MINER) {
        rt = IRONMINE;
    }
    ResourceManager *rm = ResourceManager::get_instance();
    vec2 targetVector = _target_resource != nullptr ? *_target_resource : owner->get_position();
    vec2 resource_position = rm->get_closest_resource(targetVector, rt);

    GraphManager *gm = GraphManager::get_instance();
    int index = gm->graph->get_node_with_exact_position(resource_position);
    Node *goal = gm->graph->nodes.at(index);

    return goal;
}

Node *WorkGoal::find_depot() {
    GraphManager *gm = GraphManager::get_instance();
    ResourceManager *rm = ResourceManager::get_instance();

    vec2 warehouse_position = rm->get_closest_resource(owner->get_position(), WAREHOUSE);
    int index = gm->graph->get_node_with_exact_position(warehouse_position);
    Node *goal = gm->graph->nodes.at(index);
    goal = gm->graph->find_closest_edge(goal);
    return goal;
}

void WorkGoal::set_goal_gather_resource() {
    this->sub_goals.push_front(new GatherResourceGoal(owner, resource->get_position()));
}

void WorkGoal::set_goal_drop_resources() {
    this->sub_goals.push_front(new DropResourcesGoal(owner, rt));
}

const char *WorkGoal::get_name() const {
    return "Work";
}

