//
// Created by Sander on 18-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_FIGHT_GOAL_H
#define CONSTRUCT_AND_DESTROY_FIGHT_GOAL_H

#include "types.h"
#include "goal/atomic_goal.h"

class MovingEntity;
class BaseEntity;

class FightGoal : public AtomicGoal<MovingEntity> {
private:
    BaseEntity *_enemy;
    float _last_attack_time;
public:
    FightGoal(MovingEntity *, BaseEntity*, int initiator = Initiator::AI);

    ~FightGoal();

    void activate() override;

    /*!
     * Attacks every 0.1 seconds, goal is completed if the enemy
     * or the owner entity is KIA.
     */
    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};

#endif //CONSTRUCT_AND_DESTROY_FIGHT_GOAL_H
