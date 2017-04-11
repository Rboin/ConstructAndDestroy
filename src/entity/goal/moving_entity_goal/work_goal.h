//
// Created by Sander on 19-3-2017.
//

#ifndef C_AND_D_PROJECT_WORK_GOAL_H
#define C_AND_D_PROJECT_WORK_GOAL_H

#include <entity/goal/composite_goal.h>
#include <vector>
#include "job_type.h"

class MovingEntity;

template<typename T>
class GoalEvaluator;
class Node;

class WorkGoal : public GoalComposite<MovingEntity> {
private:
    std::vector<GoalEvaluator<MovingEntity> *> _evaluators;
    Node *resource;
public:
    WorkGoal(MovingEntity *);

    void add_evaluator(GoalEvaluator<MovingEntity> *);

    /**
     * calculate the most desirable goal, based on given evaluators.
     */
    void determine_next_goal();

    void set_goal_plan_path_to_resource();

    void set_goal_plan_path_home();

    void set_goal_follow_path();

    void set_goal_gather_resource();

    void set_goal_drop_resources();

    Node* find_resource_node();

    Node* find_home_node();

    Node* find_closest_edge();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

};

#endif //C_AND_D_PROJECT_WORK_GOAL_H
