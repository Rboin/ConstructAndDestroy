//
// Created by robin on 3/11/17.
//

#include "obstacle_avoid_evaluator.h"
#include "entity/moving/moving_entity.h"
#include "entity/entity_types.h"
#include "neighbourhood_manager.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float ObstacleAvoidEvaluator::calculate_desirability(MovingEntity *t) {

    std::vector<BaseEntity *> neighbours = NeighbourhoodManager::get_instance()->get_neighbours((BaseEntity *) t);
    const float avoid_range = 100;
    if (neighbours.size() > 0) {
        BaseEntity *closest = neighbours[0];
        const float distance = t->get_position().distance(closest->get_position());
        if (closest->is(EntityType::STATIC) && distance < avoid_range) {
            _avoid_target = &closest->get_position();
            return (1 / (avoid_range-distance));
        }

    }
    return .0f;
}

void ObstacleAvoidEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_obstacle_avoidance(_avoid_target);
}

