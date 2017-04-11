//
// Created by Sander on 12-3-2017.
//

#ifndef C_AND_D_PROJECT_EXPLORE_GOAL_H
#define C_AND_D_PROJECT_EXPLORE_GOAL_H


#include "entity/goal/atomic_goal.h"

class MovingEntity;
class ResourceManager;

class ExploreGoal : public AtomicGoal<MovingEntity> {
    ResourceManager *rm;
public:
    ExploreGoal(MovingEntity *);

    ~ExploreGoal();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

};


#endif //C_AND_D_PROJECT_EXPLORE_GOAL_H
