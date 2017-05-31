//
// Created by Sander on 10-5-2017.
//

#include "behaviour/strategy/seek_strategy.h"
#include "hunt_target_goal.h"
#include "entity/player.h"
#include "graph/graph_manager.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "strategy_goal_type.h"
#include "graph/graph.h"
#include "follow_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "behaviour/behaviour.h"
#include "atomic_goal_type.h"
#include "think_goal.h"

HuntTargetGoal::HuntTargetGoal(MovingEntity *e, BaseEntity *enemy) : GoalComposite(e, HUNTTARGET) {
    _enemy = enemy;
    set_goal_plan_path_to_enemy();
    if (_enemy_node->get_index() != 0) {
        set_goal_follow_path();
    }
}

HuntTargetGoal::~HuntTargetGoal() {
    remove_all_subgoals();
    _enemy_node = nullptr;
    _enemy = nullptr;
}

void HuntTargetGoal::determine_next_goal() {
    if (this->sub_goals.size() == 0) {
        status = COMPLETED;
    } else {
        float distance = _enemy_node->get_position()->distance(_enemy->get_position());
        //If the enemy entity has moved to much we terminate this goal and
        //we set the seek to the enemy's current position, otherwise
        //the chasing entity won't move for a bit.
        if (distance > 40) {
            terminate();
            owner->get_behaviour()->remove_all();
            owner->get_behaviour()->add(TRAVERSEEDGE, new SeekStrategy());
            owner->get_behaviour()->set_target_for(TRAVERSEEDGE, &_enemy->get_position(), 1);

        }
    }
}

void HuntTargetGoal::set_goal_plan_path_to_enemy() {
    GraphManager *gm = GraphManager::get_instance();
    _enemy_node = gm->graph->nodes[gm->graph->get_node_with_position(_enemy->get_position().clone())];
    if (_enemy_node->get_index() != 0) {
        this->sub_goals.push_front(new PlanPathGoal(owner, gm->graph->find_closest_edge(_enemy_node)));
    }
}

void HuntTargetGoal::set_goal_follow_path() {
    this->sub_goals.push_front(new FollowPathGoal(owner));
}

void HuntTargetGoal::activate() {
    status = ACTIVE;
}

const int HuntTargetGoal::process() {
    activate_if_inactive();
    determine_next_goal();

    return process_subgoals();;
}

void HuntTargetGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

const char *HuntTargetGoal::get_name() const {
    return "HuntTarget";
}
