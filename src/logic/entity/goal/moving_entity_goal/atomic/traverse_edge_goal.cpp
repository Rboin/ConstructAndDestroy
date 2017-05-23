//
// Created by Sander on 14-3-2017.
//

#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "behaviour/strategy/seek_strategy.h"
#include "traverse_edge_goal.h"
#include "behaviour/behaviour.h"

TraverseEdgeGoal::TraverseEdgeGoal(MovingEntity *e, vec2 *g, int initiator) : AtomicGoal<MovingEntity>(e, TRAVERSEEDGE,
                                                                                                       initiator) {
    goal = g;
}

void TraverseEdgeGoal::activate() {
    status = ACTIVE;
    owner->get_behaviour()->add(TRAVERSEEDGE, new SeekStrategy());
    owner->get_behaviour()->set_target_for(TRAVERSEEDGE, goal, 1);
}

const int TraverseEdgeGoal::process() {
    activate_if_inactive();
    _goal_time += owner->get_delta_time();

    //Extra check to prevent the bot from getting stuck.
    if (_goal_time > 1000) {
        is_stuck();
    }

    float distance = owner->get_position().distance(*goal);
    if (distance < 5) {
        status = COMPLETED;
    }

    return status;
}

void TraverseEdgeGoal::terminate() {
    status = COMPLETED;
}

const char *TraverseEdgeGoal::get_name() const {
    return "TraverseEdge";
}

void TraverseEdgeGoal::is_stuck() {
    _goal_time = owner->get_delta_time();
    owner->get_behaviour()->remove_all();
    owner->get_behaviour()->add(TRAVERSEEDGE, new SeekStrategy());
    owner->get_behaviour()->set_target_for(TRAVERSEEDGE, goal, 1);
}
