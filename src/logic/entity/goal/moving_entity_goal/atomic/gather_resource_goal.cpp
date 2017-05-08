//
// Created by Sander on 3-4-2017.
//

#include <entity/goal/moving_entity_goal/atomic_goal_type.h>
#include <graph/node.h>
#include <entity/static/resource_manager.h>
#include "gather_resource_goal.h"
#include "entity/moving/moving_entity.h"

GatherResourceGoal::GatherResourceGoal(MovingEntity *e, vec2 *pos) : AtomicGoal<MovingEntity>(e, GATHER) {
    ResourceManager *rm = ResourceManager::get_instance();
    resource = rm->get_resource(pos);
}

void GatherResourceGoal::activate() {
    status = ACTIVE;
}

const int GatherResourceGoal::process() {
    activate_if_inactive();
    owner->carrying+= resource->gather(owner->delta_time);
    if(owner->carrying >= 5 || resource->is_depleted()){
        status = COMPLETED;
    }
    return status;
}

void GatherResourceGoal::terminate() {

}

const char *GatherResourceGoal::get_name() const {
    return "GatherResource";
}
