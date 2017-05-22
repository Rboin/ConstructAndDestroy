//
// Created by Sander on 10-5-2017.
//

#include "combat_evaluator.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "entity/moving/moving_entity.h"

const float CombatEvaluator::calculate_desirability(MovingEntity *t) {
    return 0.2;
}

void CombatEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_combat();
}
