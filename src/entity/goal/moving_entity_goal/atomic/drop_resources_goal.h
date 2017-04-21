//
// Created by Sander on 3-4-2017.
//

#ifndef C_AND_D_PROJECT_DROP_RESOURCES_GOAL_H
#define C_AND_D_PROJECT_DROP_RESOURCES_GOAL_H


#include <entity/static/resource_type.h>
#include "goal/atomic_goal.h"

class MovingEntity;

class DropResourcesGoal : public AtomicGoal<MovingEntity> {
    ResourceType rt;
public:
    /*!
     * Extracts resources from the worker and adds it to the player.
     */
    DropResourcesGoal(MovingEntity *, ResourceType);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_DROP_RESOURCES_GOAL_H
