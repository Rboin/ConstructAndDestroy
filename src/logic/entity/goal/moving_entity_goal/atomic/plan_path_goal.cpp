//
// Created by Sander on 14-3-2017.
//

#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "behaviour/strategy/seek_strategy.h"
#include "graph/graph_manager.h"
#include "plan_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "graph/graph.h"

PlanPathGoal::PlanPathGoal(MovingEntity *t, Node *g, int initiator) : AtomicGoal(t, PLANPATH, initiator) {
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
    //Popping the first edge from the path if we have more than 2.
    //This will prevent the entity from moving backwards while halfway
    //on a edge.
    if(owner->path.size() > 2){
        owner->path.pop();
    }

    terminate();
    return status;
}

void PlanPathGoal::terminate() {
    status = COMPLETED;
}

const char *PlanPathGoal::get_name() const {
    return "PlanPath";
}
