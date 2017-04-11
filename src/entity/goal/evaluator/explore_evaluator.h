//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_EXPLORE_EVALUATOR_H
#define C_AND_D_PROJECT_EXPLORE_EVALUATOR_H

#include "goal_evaluator.h"

class MovingEntity;

class ExploreEvaluator : public GoalEvaluator<MovingEntity> {
public:
    const float calculate_desirability(MovingEntity *t) override;

    void set_goal(MovingEntity *t) override;
};


#endif //C_AND_D_PROJECT_EXPLORE_EVALUATOR_H
