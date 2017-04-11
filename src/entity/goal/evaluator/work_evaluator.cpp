//
// Created by Sander on 21-3-2017.
//

#include "work_evaluator.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float WorkEvaluator::calculate_desirability(MovingEntity *t) {
    return 0.1; //because we like to work
}

void WorkEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_work();
}