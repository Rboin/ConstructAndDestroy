//
// Created by Sander on 19-3-2017.
//

#include "goal/composite_goal.h"
#include "entity/static/resource_manager.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "graph/graph_manager.h"
#include "graph/graph.h"
#include "entity/goal/moving_entity_goal/atomic/gather_resource_goal.h"
#include "entity/goal/moving_entity_goal/atomic/drop_resources_goal.h"
#include "entity/moving/moving_entity.h"
#include "work_goal.h"
#include "strategy_goal_type.h"
#include "follow_path_goal.h"
#include "entity/static/building/building_manager.h"

WorkGoal::WorkGoal(MovingEntity *e, vec2 *target_resource, int initiator) : GoalComposite(e, WORK, initiator) {
    _target_resource = target_resource;
    set_goal_plan_path_to_resource();
    if (_resource->get_index() != 0 && e->get_carrying() <= 5) {
        set_goal_follow_path();
        set_goal_gather_resource();
    }
    BuildingManager *bm = BuildingManager::get_instance();
    if(bm->has_building_type(WAREHOUSE) && e->get_carrying() > .1){
        set_goal_plan_path_home();
        set_goal_follow_path();
        set_goal_drop_resources();
    }
}

WorkGoal::~WorkGoal() {
    _resource = nullptr;
    _target_resource = nullptr;
    remove_all_subgoals();
}

void WorkGoal::determine_next_goal() {
    if (this->sub_goals.size() == 0) {
        status = COMPLETED;
    }
}

void WorkGoal::set_goal_plan_path_to_resource() {
    _resource = find_resource_node();
    if (_resource->get_index() != 0 && owner->get_carrying() <= 5) {
        this->sub_goals.push_front(new PlanPathGoal(owner, _resource));
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
    if (owner->get_job_type() == WOODCUTTER) {
        _rt = WOOD;
    }
    if (owner->get_job_type() == IRONMINER) {
        _rt = IRON;
    }
    if (owner->get_job_type() == GMINER) {
        _rt = GOLD;
    }
    if (owner->get_job_type() == SMINER) {
        _rt = STONE;
    }
    ResourceManager *rm = ResourceManager::get_instance();
    vec2 targetVector = _target_resource != nullptr ? *_target_resource : owner->get_position();
    vec2 resource_position = rm->get_closest_resource(targetVector, _rt);

    GraphManager *gm = GraphManager::get_instance();
    int index = gm->graph->get_node_with_exact_position(resource_position);
    Node *goal = gm->graph->nodes.at(index);

    return goal;
}

Node *WorkGoal::find_depot() {
    GraphManager *gm = GraphManager::get_instance();
    BuildingManager *bm = BuildingManager::get_instance();

    vec2 warehouse_position = bm->get_closest_building(owner->get_position(), WAREHOUSE);
    int index = gm->graph->get_node_with_exact_position(warehouse_position);
    Node *goal = gm->graph->nodes.at(index);
    goal = gm->graph->find_closest_edge(goal);
    return goal;
}

void WorkGoal::set_goal_gather_resource() {
    this->sub_goals.push_front(new GatherResourceGoal(owner, _resource->get_position()));
}

void WorkGoal::set_goal_drop_resources() {
    this->sub_goals.push_front(new DropResourcesGoal(owner, _rt));
}

const char *WorkGoal::get_name() const {
    return "Work";
}

