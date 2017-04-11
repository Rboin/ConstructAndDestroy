//
// Created by Sander on 3-4-2017.
//

#include <entity/goal/moving_entity_goal/atomic_goal_type.h>
#include "drop_resources_goal.h"
#include "entity/moving/moving_entity.h"

DropResourcesGoal::DropResourcesGoal(MovingEntity *e) : AtomicGoal<MovingEntity>(e, DROP) {

}

void DropResourcesGoal::activate() {
    status = ACTIVE;
}

const int DropResourcesGoal::process() {
    activate_if_inactive();
    owner->carrying-= 0.25f;
    owner->hunger+= 0.01f;
    owner->tiredness+= 0.01f;
    if(owner->carrying <= 0){
        status = COMPLETED;
    }

    return status;
}

void DropResourcesGoal::terminate() {
}

const char *DropResourcesGoal::get_name() const {
    return "DropResource";
}
