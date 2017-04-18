//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_REST_EVALUATOR_H
#define C_AND_D_PROJECT_REST_EVALUATOR_H


#include <entity/goal/moving_entity_goal/job_type.h>
#include "goal/goal_evaluator.h"

class MovingEntity;

class RestEvaluator : public GoalEvaluator<MovingEntity> {
public:
    const float calculate_desirability(MovingEntity *t) override;

    void set_goal(MovingEntity *t) override;

};


#endif //C_AND_D_PROJECT_REST_EVALUATOR_H
