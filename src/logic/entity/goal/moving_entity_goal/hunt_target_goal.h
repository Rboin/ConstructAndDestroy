//
// Created by Sander on 10-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_HUNT_TARGET_GOAL_H
#define CONSTRUCT_AND_DESTROY_HUNT_TARGET_GOAL_H


#include "types.h"
#include "goal/composite_goal.h"

class MovingEntity;

template<typename T>
class GoalEvaluator;
class Node;

class HuntTargetGoal : public GoalComposite<MovingEntity> {
private:
    Node *_enemy_node;
public:
    /*!
     * If the _enemy_node index == 0 there is no enemy available
     * so new goals won't be set because there is nothing to attack/kill.
     */
    HuntTargetGoal(MovingEntity *);

    void determine_next_goal();

    /*!
     * Plans the path to the enemy entity
     */
    void set_goal_plan_path_to_enemy();

    /*!
     * Follows the path that has been planned
     */
    void set_goal_follow_path();

    /*!
     * Searches an enemy entity.
     * An enemy entity is an entity from the opposite player.
     * @return the node on which the entity is currently closest to.
     */
    Node* find_enemy();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //CONSTRUCT_AND_DESTROY_HUNT_TARGET_GOAL_H
