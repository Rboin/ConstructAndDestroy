//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_OBSTACLE_AVOIDANCE_GOAL_H
#define C_AND_D_PROJECT_OBSTACLE_AVOIDANCE_GOAL_H

#include "entity/goal/atomic_goal.h"
#include "types.h"

class MovingEntity;

class ObstacleAvoidanceGoal : public AtomicGoal<MovingEntity> {
private:
    vec2 *_avoid_target;
    float _max_range;
public:
    ObstacleAvoidanceGoal(MovingEntity *t, vec2 *);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_OBSTACLE_AVOIDANCE_GOAL_H
