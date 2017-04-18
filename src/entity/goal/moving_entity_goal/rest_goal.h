//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_REST_GOAL_H
#define C_AND_D_PROJECT_REST_GOAL_H


#include <goal/composite_goal.h>
#include <vector>
#include "job_type.h"

class MovingEntity;

template<typename T>
class GoalEvaluator;
class Node;

class RestGoal : public GoalComposite<MovingEntity> {
public:
    RestGoal(MovingEntity *);

    void determine_next_goal();

    void set_goal_plan_path_to_campfire();

    void set_goal_follow_path();

    void set_goal_sleep();

    Node* find_campfire_node();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

};


#endif //C_AND_D_PROJECT_REST_GOAL_H
