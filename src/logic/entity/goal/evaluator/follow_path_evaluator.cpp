//
// Created by bouwm on 22-3-2017.
//

#include <entity/goal/moving_entity_goal/initiator.h>
#include "follow_path_evaluator.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float FollowPathEvaluator::calculate_desirability(MovingEntity *t) {
    Goal<MovingEntity>* goal = t->get_brain()->get_active_goal();

    if (goal && goal->get_initiator() == Initiator::PLAYER) {
        return 1;
    }

    // Has a low constant desirability.
    return 0.02;
}

void FollowPathEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_follow_path();
}