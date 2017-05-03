//
// Created by Sander on 3-4-2017.
//

#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "entity/player_manager.h"
#include "entity/moving/moving_entity.h"
#include "drop_resources_goal.h"
#include "entity/player.h"

DropResourcesGoal::DropResourcesGoal(MovingEntity *e, ResourceType r) : AtomicGoal<MovingEntity>(e, DROP) {
    rt = r;
}

void DropResourcesGoal::activate() {
    status = ACTIVE;
}

const int DropResourcesGoal::process() {
    activate_if_inactive();
    owner->get_player()->resources.add_resources(rt,owner->carrying);
    owner->carrying = 0.0f;
    status = COMPLETED;
    return status;
}

void DropResourcesGoal::terminate() {
}

const char *DropResourcesGoal::get_name() const {
    return "DropResource";
}
