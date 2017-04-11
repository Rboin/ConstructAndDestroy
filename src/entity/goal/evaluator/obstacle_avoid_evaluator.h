//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_OBSTACLEAVOIDEVALUATOR_H
#define C_AND_D_PROJECT_OBSTACLEAVOIDEVALUATOR_H

#include "goal_evaluator.h"
#include "types.h"
class MovingEntity;

class ObstacleAvoidEvaluator : public GoalEvaluator<MovingEntity> {
private:
    vec2 *_avoid_target;
public:
    const float calculate_desirability(MovingEntity *) override;
    void set_goal(MovingEntity *) override;
};


#endif //C_AND_D_PROJECT_OBSTACLEAVOIDEVALUATOR_H
