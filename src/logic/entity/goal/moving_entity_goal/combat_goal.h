//
// Created by Sander on 10-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_COMBAT_GOAL_H
#define CONSTRUCT_AND_DESTROY_COMBAT_GOAL_H


#include "goal/composite_goal.h"

class MovingEntity;

template<typename T>
class GoalEvaluator;
class Node;

class CombatGoal : public GoalComposite<MovingEntity> {
public:
    
    CombatGoal(MovingEntity *);

    void set_goal_hunt_target();

    void set_goal_attack_enemy();

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

};


#endif //CONSTRUCT_AND_DESTROY_COMBAT_GOAL_H
