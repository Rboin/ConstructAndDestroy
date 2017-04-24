//
// Created by Sander on 21-3-2017.
//

#include "gather_resource_evaluator.h"
#include "entity/static/resource_manager.h"
#include "entity/goal/moving_entity_goal/job_type.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float GatherResourceEvaluator::calculate_desirability(MovingEntity *t) {
    ResourceManager *rm = ResourceManager::get_instance();
    vec2 resource_position = rm->get_closest_resource(t->get_position(), rm->get_resource_type(t->job_type));

    //if there is a resource close and we don't have maximum carrying capacity continue gathering;
    if(resource_position.distance(t->get_position()) < 1 && t->carrying < 100) {
        return 1.0;
    }
    return 0.0;
}

void GatherResourceEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_wander();
}
