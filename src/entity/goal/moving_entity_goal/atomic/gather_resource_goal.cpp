//
// Created by Sander on 3-4-2017.
//

#include <entity/goal/moving_entity_goal/atomic_goal_type.h>
#include "gather_resource_goal.h"
#include "entity/moving/moving_entity.h"

GatherResourceGoal::GatherResourceGoal(MovingEntity *e) : AtomicGoal<MovingEntity>(e, GATHER) {

}

void GatherResourceGoal::activate() {
    status = ACTIVE;
}

const int GatherResourceGoal::process() {
    activate_if_inactive();
    owner->carrying+= 0.05f;
    owner->hunger+= 0.02f;
    owner->tiredness+= 0.015f;
    if(owner->carrying >= 100){
        status = COMPLETED;
    }

    return status;
}

void GatherResourceGoal::terminate() {

}

const char *GatherResourceGoal::get_name() const {
    return "GatherResource";
}
