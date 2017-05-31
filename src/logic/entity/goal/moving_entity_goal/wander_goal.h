//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_WANDER_GOAL_H
#define C_AND_D_PROJECT_WANDER_GOAL_H

#include "goal/composite_goal.h"

class MovingEntity;

class WanderGoal : public GoalComposite<MovingEntity> {
public:
    WanderGoal(MovingEntity *, int initiator = Initiator::AI);

    ~WanderGoal();

    void determine_next_goal();

    void activate() override;

    Node* choose_random_goal();

    void set_goal_plan_path();

    void set_goal_follow_path();

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

    int random_number(int);
};


#endif //C_AND_D_PROJECT_WANDER_GOAL_H
