//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_ATOMIC_GOAL_H
#define C_AND_D_PROJECT_ATOMIC_GOAL_H

#include <stdexcept>
#include <entity/goal/moving_entity_goal/level_type.h>
#include "goal.h"

template<typename T>
class AtomicGoal : public Goal<T> {
public:
    AtomicGoal(T *t, int gt) : Goal<T>(t, gt, ATOMIC) {};
    AtomicGoal(T *t, int gt, int init) : Goal<T>(t, gt, ATOMIC, init) {};

    void add_subgoal(Goal<T> *goal) {
        throw std::invalid_argument("Can not add a subgoal to an atomic goal.");
    };

    virtual ~AtomicGoal() {};

    virtual void activate() = 0;

    virtual const int process() = 0;

    virtual void terminate() = 0;
};


#endif //C_AND_D_PROJECT_ATOMIC_GOAL_H
