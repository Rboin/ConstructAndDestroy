//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_EAT_GOAL_H
#define C_AND_D_PROJECT_EAT_GOAL_H

#include <entity/goal/atomic_goal.h>

class MovingEntity;

class EatGoal : public AtomicGoal<MovingEntity> {
public:
    EatGoal(MovingEntity *);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_EAT_GOAL_H
