//
// Created by Sander on 10-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_HUNT_TARGET_GOAL_H
#define CONSTRUCT_AND_DESTROY_HUNT_TARGET_GOAL_H


#include "types.h"
#include "goal/composite_goal.h"
#include "vector.h"

class MovingEntity;

template<typename T>
class GoalEvaluator;
class Node;

class HuntTargetGoal : public GoalComposite<MovingEntity> {
private:
    Node *_enemy_node;
    MovingEntity *_enemy;
public:
    /*!
     * If the _enemy_node index == 0 there is no enemy available
     * so new goals won't be set because there is nothing to attack/kill.
     */
    HuntTargetGoal(MovingEntity *, MovingEntity*);

    /*!
     * If the sub_goals size == 0 then this goal's status will be set to completed.
     * Otherwise, we check how far the enemy is from its 'old node' if the distance
     * is greater than a certain threshold this goal will be terminated, and we set a Seek
     * to the enemy's current position. If we don't do this the bot will stand still for a bit.
     */
    void determine_next_goal();

    /*!
     * Plans the path to the enemy entity
     */
    void set_goal_plan_path_to_enemy();

    /*!
     * Follows the path that has been planned
     */
    void set_goal_follow_path();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //CONSTRUCT_AND_DESTROY_HUNT_TARGET_GOAL_H
