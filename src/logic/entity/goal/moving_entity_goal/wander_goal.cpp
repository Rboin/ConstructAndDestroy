//
// Created by robin on 3/11/17.
//

#include "graph/graph.h"
#include "graph/graph_manager.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "wander_goal.h"
#include "entity/moving/moving_entity.h"
#include "behaviour/behaviour.h"
#include "behaviour/strategy/wander_strategy.h"
#include "follow_path_goal.h"
#include "strategy_goal_type.h"

WanderGoal::WanderGoal(MovingEntity *e, int initiator) : GoalComposite<MovingEntity>(e, WANDER, initiator) {
    set_goal_plan_path();
    set_goal_follow_path();
}

WanderGoal::~WanderGoal() {
    remove_all_subgoals();
}

void WanderGoal::determine_next_goal() {
    if (this->sub_goals.size() == 0) {
        status = COMPLETED;
    }
}

Node* WanderGoal::choose_random_goal() {
    GraphManager *gm = GraphManager::get_instance();
    int i = random_number(gm->graph->nodes.size());
    return gm->graph->nodes[i];
}

void WanderGoal::set_goal_plan_path() {
    this->sub_goals.push_front(new PlanPathGoal(owner, choose_random_goal()));

}

void WanderGoal::set_goal_follow_path() {
    this->sub_goals.push_front(new FollowPathGoal(owner));
}

void WanderGoal::activate() {
    status = ACTIVE;
}

const int WanderGoal::process() {
    activate_if_inactive();
    determine_next_goal();
    return process_subgoals();
}

void WanderGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

const char *WanderGoal::get_name() const {
    return "Wander";
}

int WanderGoal::random_number(int size)
{
    static int number = 1;
    number = (221 * number + 1) % size;
    return number;
}


