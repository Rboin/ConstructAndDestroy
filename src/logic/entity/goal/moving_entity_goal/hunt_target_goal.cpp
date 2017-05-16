//
// Created by Sander on 10-5-2017.
//

#include "behaviour/strategy/seek_strategy.h"
#include "hunt_target_goal.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "graph/graph_manager.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "strategy_goal_type.h"
#include "graph/graph.h"
#include "follow_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "behaviour/behaviour.h"
#include "atomic_goal_type.h"

HuntTargetGoal::HuntTargetGoal(MovingEntity *e) : GoalComposite(e, HUNTTARGET) {
    set_goal_plan_path_to_enemy();
    if (_enemy_node->get_index() != 0) {
        set_goal_follow_path();
    }
}

void HuntTargetGoal::determine_next_goal() {
    if (this->sub_goals.size() == 0) {
        status = COMPLETED;
    }

    Node *enemy_node = find_enemy();
    float distance = enemy_node->get_position()->distance(_enemy_node->get_position()->clone());
    //If the enemy entity has moved to much we terminate this goal and
    //we set the seek to the enemy's current position, otherwise
    //the chasing entity won't move for a bit.
    if (distance > 40) {
        terminate();
        owner->get_behaviour()->add(TRAVERSEEDGE, new SeekStrategy());
        owner->get_behaviour()->set_target_for(TRAVERSEEDGE, enemy_node->get_position(), 1);

    }
}

void HuntTargetGoal::set_goal_plan_path_to_enemy() {
    GraphManager *gm = GraphManager::get_instance();
    _enemy_node = find_enemy();
    if (_enemy_node->get_index() != 0) {
        this->sub_goals.push_front(new PlanPathGoal(owner, gm->graph->find_closest_edge(_enemy_node)));
    }
}

void HuntTargetGoal::set_goal_follow_path() {
    this->sub_goals.push_front(new FollowPathGoal(owner));
}

Node *HuntTargetGoal::find_enemy() {
    GraphManager *gm = GraphManager::get_instance();
    PlayerManager *pm = PlayerManager::get_instance();
    //todo:: change this to opposite player
    Player *enemy_player = pm->get_player(1);

    //todo:: change this, maybe pick the closest or the most threatening enemy
    MovingEntity *enemy_entity = enemy_player->units.at(0);
    int index = gm->graph->get_node_with_position(enemy_entity->get_position());
    return gm->graph->nodes[index];
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
