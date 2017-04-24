//
// Created by robin on 3/11/17.
//

#include "explore_evaluator.h"
#include "entity/static/resource_manager.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float ExploreEvaluator::calculate_desirability(MovingEntity *t) {
    float desirability = 0.0;

    //If there isn't a resource close we want to explore, when we find a resource we can stop exploring.
    ResourceManager *rm = ResourceManager::get_instance();
    ResourceType rt;
    if (t->job_type == WOODCUTTER) { rt = TREE; }
    if (t->job_type == MINER) { rt = IRONMINE; }
    vec2 resource_position = rm->get_closest_resource(t->get_position(),rt);
    float distance = resource_position.distance(t->get_position());
    if (distance > 50) {
        desirability = .02;
    }
    return desirability;
}

void ExploreEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_explore();
}
