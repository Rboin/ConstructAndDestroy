//
// Created by Sander on 14-3-2017.
//

#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "behaviour/strategy/seek_strategy.h"
#include "traverse_edge_goal.h"
#include "behaviour/behaviour.h"

TraverseEdgeGoal::TraverseEdgeGoal(MovingEntity *e, vec2 *g) : AtomicGoal<MovingEntity>(e, TRAVERSEEDGE) {
    goal = g;
}

void TraverseEdgeGoal::activate() {
    status = ACTIVE;
    owner->get_behaviour()->add(TRAVERSEEDGE, new SeekStrategy());
}

const int TraverseEdgeGoal::process() {
    activate_if_inactive();

    if (owner->get_behaviour()->has_behaviour(TRAVERSEEDGE)) {
        owner->get_behaviour()->set_target_for(TRAVERSEEDGE, goal, 1);

        float distance = owner->get_position().distance(*goal);
        if (distance < 5) {
            status = COMPLETED;
        }
    }
    return status;
}

void TraverseEdgeGoal::terminate() {
    status = COMPLETED;
    owner->get_behaviour()->remove(TRAVERSEEDGE);
}

const char *TraverseEdgeGoal::get_name() const {
    return "TraverseEdge";
}
