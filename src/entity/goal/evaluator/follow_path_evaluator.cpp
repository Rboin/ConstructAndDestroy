//
// Created by bouwm on 22-3-2017.
//

#include "follow_path_evaluator.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float FollowPathEvaluator::calculate_desirability(MovingEntity *t) {
    // Has a low constant desirability.
    return 0.02;
}

void FollowPathEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_follow_path();
}