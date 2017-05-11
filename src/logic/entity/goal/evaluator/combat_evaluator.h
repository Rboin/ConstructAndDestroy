//
// Created by Sander on 10-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_COMBAT_EVALUATOR_H
#define CONSTRUCT_AND_DESTROY_COMBAT_EVALUATOR_H

#include "goal/goal_evaluator.h"

class MovingEntity;

class CombatEvaluator: public GoalEvaluator<MovingEntity> {
public:
    const float calculate_desirability(MovingEntity *t) override;

    void set_goal(MovingEntity *t) override;

};


#endif //CONSTRUCT_AND_DESTROY_COMBAT_EVALUATOR_H
