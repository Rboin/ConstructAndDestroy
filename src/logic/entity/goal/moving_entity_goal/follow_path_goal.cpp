//
// Created by Sander on 14-3-2017.
//

#include <iostream>
#include "follow_path_goal.h"
#include "entity/goal/moving_entity_goal/atomic/traverse_edge_goal.h"
#include "graph/graph.h"
#include "entity/moving/moving_entity.h"
#include "wander_goal.h"
#include "strategy_goal_type.h"
#include "behaviour/behaviour.h"
#include "atomic_goal_type.h"

FollowPathGoal::FollowPathGoal(MovingEntity *e, int initiator) : GoalComposite(e, FOLLOWPATH, initiator) {
}

void FollowPathGoal::set_goal_traverse_edge(vec2 *g) {
    this->sub_goals.push_front(new TraverseEdgeGoal(owner, g));
}

void FollowPathGoal::activate() {
    if(owner->get_path().size()!= 0){
        status = ACTIVE;
        set_goal_traverse_edge(owner->get_path().top());
        owner->get_path().pop();
    }else{
        status = COMPLETED;
    }
}

const int FollowPathGoal::process() {
    activate_if_inactive();
    status = process_subgoals();
    if(status == COMPLETED && !owner->get_path().empty()){
        activate();
    }
    return status;
}

void FollowPathGoal::terminate() {
    remove_all_subgoals();
    owner->get_behaviour()->remove(TRAVERSEEDGE);
}

const char *FollowPathGoal::get_name() const {
    return "FollowPath";
}

