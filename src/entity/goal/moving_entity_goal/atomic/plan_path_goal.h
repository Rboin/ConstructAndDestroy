//
// Created by Sander on 14-3-2017.
//

#ifndef C_AND_D_PROJECT_PLANPATH_H
#define C_AND_D_PROJECT_PLANPATH_H

#include <vector>
#include <types.h>
#include <queue>
#include <entity/goal/atomic_goal.h>

class MovingEntity;

class Node;

class PlanPathGoal : public AtomicGoal<MovingEntity> {
    Node *start;
    Node *goal;
public:
    PlanPathGoal(MovingEntity *, Node *, Node *);

    void activate() override;

    const int process() override;

    void terminate() override;

    std::queue<vec2 *> path;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_PLANPATH_H
