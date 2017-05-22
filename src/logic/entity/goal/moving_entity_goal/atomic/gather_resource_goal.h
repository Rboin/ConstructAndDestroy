//
// Created by Sander on 3-4-2017.
//

#ifndef C_AND_D_PROJECT_GATHER_RESOURCE_GOAL_H
#define C_AND_D_PROJECT_GATHER_RESOURCE_GOAL_H

#include "goal/atomic_goal.h"

class MovingEntity;

class GatherResourceGoal : public AtomicGoal<MovingEntity> {
private:
    ResourceEntity *_resource;
public:
    GatherResourceGoal(MovingEntity *, vec2*, int initiator = Initiator::AI);

    void activate() override;

    /*!
     * Extracts resources from a resource entity and adds them to the worker.
     * This goal is completed when the worker is carrying 5 units or
     * when the resource is depleted.
     * @return
     */
    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};

#endif //C_AND_D_PROJECT_GATHER_RESOURCE_GOAL_H
