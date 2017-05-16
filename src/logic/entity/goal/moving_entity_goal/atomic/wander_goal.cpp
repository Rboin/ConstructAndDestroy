//
// Created by robin on 3/11/17.
//

#include "wander_goal.h"
#include "entity/goal/moving_entity_goal/atomic_goal_type.h"
#include "entity/moving/moving_entity.h"
#include "behaviour/behaviour.h"
#include "behaviour/strategy/wander_strategy.h"

WanderGoal::WanderGoal(MovingEntity *e, int initiator) : AtomicGoal<MovingEntity>(e, WANDER, initiator) {}

WanderGoal::~WanderGoal() {}

void WanderGoal::activate() {
    status = ACTIVE;
    owner->get_behaviour()->add(WANDER, new WanderStrategy());
}

const int WanderGoal::process() {
    activate_if_inactive();
    return status;
}

void WanderGoal::terminate() {
    owner->get_behaviour()->remove(WANDER);
}

const char *WanderGoal::get_name() const {
    return "Wander";
}
