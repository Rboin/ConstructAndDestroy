//
// Created by Sander on 10-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_COMBAT_GOAL_H
#define CONSTRUCT_AND_DESTROY_COMBAT_GOAL_H


#include "goal/composite_goal.h"
#include "strategy_goal_type.h"

class MovingEntity;
class BuildingEntity;

template<typename T>
class GoalEvaluator;
class Node;

class CombatGoal : public GoalComposite<MovingEntity> {
private:
    MovingEntity *_enemy;
    BuildingEntity *_building;
public:
    /*!
     * A couple of things are happening in the constructor:
     *  1. If this goal is initiated with an enemy it means the owner is getting attacked by an enemy in close
     *      proximity, thus we don't have to 'hunt for a target'.
     *  2. If there isn't an enemy we will search for one from the opposite player, if there isn't any enemy
     *      the goals status will be set to completed.
     *  3. If there is an enemy, we will hunt it down and once we are close we will try to kill it.
     */
    CombatGoal(MovingEntity *,MovingEntity* = nullptr);

    /*!
     * This method sets the 'hunt target goal' if the requirements are met. If there is an enemy close we won't set,
     *  hunt target, because we are already close. We will however activate the 'combat goal' of the enemy entity.
     */
    void set_goal_hunt_target();

    void set_goal_attack_enemy();

    void set_goal_move_to_building(Player *);

    void set_goal_attack_building();

    /*!
     * Checks whether or not the given sub goal is completed.
     */
    bool sub_goal_is_completed(StrategyGoalType agt);

    void activate() override;

    /*!
     * Here we check if 'hunt target' is completed, if so, it means we have traversed to a certain location,
     * however there isn't an enemy close. So we will terminate the combat goal and try again. If we don't terminate it
     * at this point we will get stuck in fight.
     */
    const int process() override;

    void terminate() override;

    const char *get_name() const override;

};


#endif //CONSTRUCT_AND_DESTROY_COMBAT_GOAL_H
