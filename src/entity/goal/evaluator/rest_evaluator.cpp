//
// Created by Sander on 4-4-2017.
//

#include "rest_evaluator.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float RestEvaluator::calculate_desirability(MovingEntity *t) {
    //if tiredness is greater then 100 we probably want to rest
    if(t->tiredness > 100){
        return .5f;
    }
    return 0.01;
}

void RestEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_rest();
}