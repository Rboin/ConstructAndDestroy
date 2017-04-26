//
// Created by Sander on 14-3-2017.
//

#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "behaviour/strategy/seek_strategy.h"
#include "graph/graph_manager.h"
#include <cmath>
#include "plan_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "graph/graph.h"

PlanPathGoal::PlanPathGoal(MovingEntity *t, Node *g) : AtomicGoal(t, PLANPATH) {
    status = ACTIVE;
    goal = g;
}

void PlanPathGoal::activate() {
    status = ACTIVE;
}

const int PlanPathGoal::process() {
    GraphManager *gm = GraphManager::get_instance();
    Node *n = gm->graph->nodes[gm->graph->get_node_with_position(owner->get_position().clone())];
    owner->path = gm->graph->a_star_path(n,goal);

    terminate();
    return status;
}

void PlanPathGoal::terminate() {
    status = COMPLETED;
}

const char *PlanPathGoal::get_name() const {
    return "PlanPath";
}
