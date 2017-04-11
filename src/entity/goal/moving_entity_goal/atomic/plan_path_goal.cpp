//
// Created by Sander on 14-3-2017.
//

#include <entity/goal/moving_entity_goal/atomic_goal_type.h>
#include <behaviour/strategy/seek_strategy.h>
#include <graph/graph_manager.h>
#include <cmath>
#include "plan_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "graph/graph.h"

PlanPathGoal::PlanPathGoal(MovingEntity *t, Node *s, Node *g) : AtomicGoal(t, PLANPATH) {
    status = ACTIVE;
    start = s;
    goal = g;
    GraphManager *gm = GraphManager::get_instance();
    owner->path = gm->graph->a_star_path(start,goal);
}

void PlanPathGoal::activate() {
    status = ACTIVE;
}

const int PlanPathGoal::process() {
    terminate();
    return status;
}

void PlanPathGoal::terminate() {
    status = COMPLETED;
}

const char *PlanPathGoal::get_name() const {
    return "PlanPath";
}
