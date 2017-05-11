//
// Created by Sander on 4-4-2017.
//

#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "entity/moving/moving_entity.h"
#include "sleep_goal.h"

SleepGoal::SleepGoal(MovingEntity *e, int initiator) : AtomicGoal<MovingEntity>(e, SLEEP, initiator) {
    tiredness_start = e->tiredness;
}

void SleepGoal::activate() {
    status = ACTIVE;
}

const int SleepGoal::process() {
    activate_if_inactive();
    owner->tiredness -= 0.01f;
    owner->hunger += 0.01f;
    if (tiredness_start - owner->tiredness > 75) {
        status = COMPLETED;
    }
    return status;
}

void SleepGoal::terminate() {
    status = COMPLETED;
}

const char *SleepGoal::get_name() const {
    return "Sleep";
}
