//
// Created by robin on 3/11/17.
//

#include <entity/goal/moving_entity_goal/atomic_goal_type.h>
#include <behaviour/strategy/obstacle_avoidance_strategy.h>
#include "obstacle_avoidance_goal.h"
#include "neighbourhood_manager.h"
#include "entity/moving/moving_entity.h"
#include "vector.h"
#include "behaviour/behaviour.h"

ObstacleAvoidanceGoal::ObstacleAvoidanceGoal(MovingEntity *t, vec2 *avoid_target) :
        AtomicGoal(t, OBSTACLE_AVOIDANCE) {
    _avoid_target = avoid_target;
    _max_range = 100;
}

void ObstacleAvoidanceGoal::activate() {
    status = ACTIVE;
    ObstacleAvoidanceStrategy *strategy = new ObstacleAvoidanceStrategy();
    strategy->set_targets(_avoid_target);
    owner->get_behaviour()->add(OBSTACLE_AVOIDANCE, strategy);
}

const int ObstacleAvoidanceGoal::process() {
    activate_if_inactive();
    float distance = owner->get_position().distance(*_avoid_target);
    if(distance > _max_range) status = COMPLETED;
    else {
        if(owner->get_behaviour()->has_behaviour(OBSTACLE_AVOIDANCE))
            owner->get_behaviour()->set_target_for(OBSTACLE_AVOIDANCE, _avoid_target, 1);
    }
    return status;
}

void ObstacleAvoidanceGoal::terminate() {
    owner->get_behaviour()->remove(OBSTACLE_AVOIDANCE);
}

const char *ObstacleAvoidanceGoal::get_name() const {
    return "ObstacleAvoidance";
}
