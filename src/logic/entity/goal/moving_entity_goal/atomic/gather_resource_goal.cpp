//
// Created by Sander on 3-4-2017.
//

#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "graph/node.h"
#include "entity/static/resource_manager.h"
#include "gather_resource_goal.h"
#include "entity/moving/moving_entity.h"

GatherResourceGoal::GatherResourceGoal(MovingEntity *e, vec2 *pos, int initiator) : AtomicGoal<MovingEntity>(e, GATHER,
                                                                                                             initiator) {
    ResourceManager *rm = ResourceManager::get_instance();
    _resource = rm->get_resource(pos);
}

GatherResourceGoal::~GatherResourceGoal() {
    _resource = nullptr;
}

void GatherResourceGoal::activate() {
    status = ACTIVE;
}

const int GatherResourceGoal::process() {
    activate_if_inactive();
    owner->set_carrying(owner->get_carrying() + _resource->gather(owner->get_delta_time()));
    if (owner->get_carrying() >= 5 || _resource->is_depleted()) {
        status = COMPLETED;
    }
    return status;
}

void GatherResourceGoal::terminate() {

}

const char *GatherResourceGoal::get_name() const {
    return "GatherResource";
}
