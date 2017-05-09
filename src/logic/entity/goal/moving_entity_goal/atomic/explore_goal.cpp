//
// Created by Sander on 12-3-2017.
//

#include "vector.h"
#include "behaviour/strategy/explore_strategy.h"
#include "entity/static/resource_manager.h"
#include "behaviour/strategy/seek_strategy.h"
#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "entity/moving/moving_entity.h"
#include "behaviour/behaviour.h"
#include "explore_goal.h"

ExploreGoal::ExploreGoal(MovingEntity *e, int initiator) : AtomicGoal<MovingEntity>(e, EXPLORE, initiator) {
    rm = ResourceManager::get_instance();
}

ExploreGoal::~ExploreGoal() {
}

void ExploreGoal::activate() {
    status = ACTIVE;
    owner->get_behaviour()->add(EXPLORE, new ExploreStrategy());
}

const int ExploreGoal::process() {
    activate_if_inactive();

    vec2 resource_position = rm->get_closest_resource(owner->get_position());
    float distance = resource_position.distance(owner->get_position());

    if (distance < 50) {
        status = COMPLETED;
    }

    return status;
}

void ExploreGoal::terminate() {
    owner->get_behaviour()->remove(EXPLORE);
    status = COMPLETED;
}

const char *ExploreGoal::get_name() const {
    return "Explore";
}
