//
// Created by Sander on 19-3-2017.
//

#ifndef C_AND_D_PROJECT_WORK_GOAL_H
#define C_AND_D_PROJECT_WORK_GOAL_H

#include <goal/composite_goal.h>
#include <vector>
#include "job_type.h"
#include "entity/static/resource_type.h"

class MovingEntity;

template<typename T>
class GoalEvaluator;
class Node;

class WorkGoal : public GoalComposite<MovingEntity> {
private:
    std::vector<GoalEvaluator<MovingEntity> *> _evaluators;
    Node *resource;
    ResourceType rt;
public:
    /*!
     * The constructor of the work goal.
     * If the resource index == 0 there is no resource available with more then 10 units
     * so all the sub goals will be removed and new goals won't be set because there is nothing to collect.
     */
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

    /*!
     * @return the closest resource node the fits the entities job type.
     */
    Node* find_resource_node();

    /*!
     * @return the closest depot node
     */
    Node* find_depot();

    /*!
     * This function prevents that entities will get stuck in resource entities.
     * @return the closest node that has neighbors so a path can be planned.
     */
    Node* find_closest_edge();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

};

#endif //C_AND_D_PROJECT_WORK_GOAL_H
