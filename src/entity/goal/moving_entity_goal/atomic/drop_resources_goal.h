//
// Created by Sander on 3-4-2017.
//

#ifndef C_AND_D_PROJECT_DROP_RESOURCES_GOAL_H
#define C_AND_D_PROJECT_DROP_RESOURCES_GOAL_H


#include "goal/atomic_goal.h"

class MovingEntity;

class DropResourcesGoal : public AtomicGoal<MovingEntity> {
public:
    DropResourcesGoal(MovingEntity *);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_DROP_RESOURCES_GOAL_H
