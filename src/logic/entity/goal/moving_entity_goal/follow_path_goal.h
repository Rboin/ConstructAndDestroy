//
// Created by Sander on 14-3-2017.
//

#ifndef C_AND_D_PROJECT_FOLLOW_PATH_GOAL_H
#define C_AND_D_PROJECT_FOLLOW_PATH_GOAL_H

#include <vector>
#include <queue>
#include "types.h"
#include "goal/composite_goal.h"

class MovingEntity;

class FollowPathGoal : public GoalComposite<MovingEntity> {
public:
    FollowPathGoal(MovingEntity *, int initiator = Initiator::AI);

    void set_goal_traverse_edge(vec2*);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};

#endif //C_AND_D_PROJECT_FOLLOW_PATH_GOAL_H
