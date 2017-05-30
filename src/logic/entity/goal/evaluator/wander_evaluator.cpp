//
// Created by robin on 3/11/17.
//

#include "wander_evaluator.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "entity/goal/moving_entity_goal/wander_goal.h"

const float WanderEvaluator::calculate_desirability(MovingEntity *t) {
    // This has low desirability, because you don't actually want to just wander around.
    // You only want this when there's nothing else to do.
    return 0.01;
}

void WanderEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_wander();
}
