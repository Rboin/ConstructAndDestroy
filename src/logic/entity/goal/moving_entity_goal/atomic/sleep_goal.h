//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_SLEEP_GOAL_H
#define C_AND_D_PROJECT_SLEEP_GOAL_H


#include <goal/atomic_goal.h>

class MovingEntity;

class SleepGoal : public AtomicGoal<MovingEntity> {
private:
    float tiredness_start;
public:
    SleepGoal(MovingEntity *);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_SLEEP_GOAL_H
