//
// Created by Sander on 4-4-2017.
//

#include "eat_evaluator.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

const float EatEvaluator::calculate_desirability(MovingEntity *t) {
    //if hunger is greater then 100 we probably want to eat, also setting this value
    //a bit higher then the sleep evaluator
    if(t->hunger > 100){
        return .6f;
    }
    return 0.01;
}

void EatEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_go_eat();
}