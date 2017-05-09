//
// Created by Sander on 4-4-2017.
//

#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "entity/moving/moving_entity.h"
#include "eat_goal.h"


EatGoal::EatGoal(MovingEntity *e, int initiator) : AtomicGoal<MovingEntity>(e, EAT, initiator) {
}

void EatGoal::activate() {
    status = ACTIVE;
}

const int EatGoal::process() {
    activate_if_inactive();
    owner->tiredness += 0.005f;
    owner->hunger -= 0.1f;
    if (owner->hunger < 5) {
        status = COMPLETED;
    }
    return status;
}

void EatGoal::terminate() {
    status = COMPLETED;
}

const char *EatGoal::get_name() const {
    return "Eat";
}
