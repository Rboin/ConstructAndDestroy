//
// Created by Sander on 19-3-2017.
//

#ifndef C_AND_D_PROJECT_WORK_GOAL_H
#define C_AND_D_PROJECT_WORK_GOAL_H

#include "goal/composite_goal.h"
#include <vector>
#include "types.h"
#include "job_type.h"
#include "entity/static/resource_type.h"

class MovingEntity;
class Node;

class WorkGoal : public GoalComposite<MovingEntity> {
private:
    Node *_resource;
    ResourceType _rt;
    vec2* _target_resource;
public:
    /*!
     * The constructor of the work goal.
     * If the resource index == 0 there is no resource available with more then 100 units
     * so new goals won't be set because there is nothing to collect.
     */
    WorkGoal(MovingEntity *, vec2* target_resource = nullptr, int initiator = Initiator::AI);

    ~WorkGoal();

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

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

};

#endif //C_AND_D_PROJECT_WORK_GOAL_H
