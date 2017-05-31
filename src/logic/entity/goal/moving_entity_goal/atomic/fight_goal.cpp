//
// Created by Sander on 18-5-2017.
//

#include "entity/entity_marks.h"
#include "world/world.h"
#include "entity/moving/moving_entity.h"
#include "fight_goal.h"
#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "behaviour/behaviour.h"
#include "entity/player.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

FightGoal::FightGoal(MovingEntity *e, BaseEntity *enemy, int initiator) : AtomicGoal<MovingEntity>(e, FIGHT,
                                                                                                   initiator) {
    _last_attack_time = 0;
    _enemy = enemy;
}

FightGoal::~FightGoal() {
    _enemy = nullptr;
}

void FightGoal::activate() {
    owner->get_behaviour()->remove_all();
    status = ACTIVE;
}

const int FightGoal::process() {
    activate_if_inactive();

    _last_attack_time += owner->get_delta_time();
    if(_last_attack_time > 100) {

        _enemy->attack(owner->get_attack_damage());
        _last_attack_time = 0;
    }

    //If the owners health gets below 0, it has died and can be removed from the game.
    if(owner->get_health() <= 0) {
        owner->set_engaged(false);
        owner->add_mark(EntityMark::DEAD);
    }
        //Enemy is killed and the goal is completed.
    else if(_enemy->get_health() <= 0) {
        status = COMPLETED;
        owner->get_brain()->resume_sub_goals();
        _enemy->add_mark(EntityMark::DEAD);
    }
    return status;
}

void FightGoal::terminate() {
    status = COMPLETED;
}

const char *FightGoal::get_name() const {
    return nullptr;
}
