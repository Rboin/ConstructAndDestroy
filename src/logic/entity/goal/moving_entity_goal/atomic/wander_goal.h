//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_WANDER_GOAL_H
#define C_AND_D_PROJECT_WANDER_GOAL_H

#include "goal/atomic_goal.h"

class MovingEntity;

class WanderGoal : public AtomicGoal<MovingEntity> {
public:
    WanderGoal(MovingEntity *);

    ~WanderGoal();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_WANDER_GOAL_H
