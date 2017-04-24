//
// Created by bouwm on 22-3-2017.
//

#ifndef C_AND_D_PROJECT_FOLLOW_PATH_EVALUATOR_H
#define C_AND_D_PROJECT_FOLLOW_PATH_EVALUATOR_H


#include "goal/goal_evaluator.h"

class MovingEntity;

class FollowPathEvaluator : public GoalEvaluator<MovingEntity> {
public:
    const float calculate_desirability(MovingEntity *t) override;

    void set_goal(MovingEntity *t) override;
};



#endif //C_AND_D_PROJECT_FOLLOW_PATH_EVALUATOR_H
