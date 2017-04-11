//
// Created by robin on 3/1/17.
//

#include "arrive_strategy.h"
#include "entity/moving/moving_entity.h"

vec2 ArriveStrategy::calculate_force(MovingEntity &e, std::vector<BaseEntity *> neighbourhood) {
    vec2 heading = (*_targets) - e.get_position();
    float distance;
    if ((distance = heading.length()) != 0) {
        float deceleration = 3 / .005f;
        float speed = distance / deceleration;
        speed = std::min(speed, e.get_max_speed());
        vec2 desired = heading * (speed / distance);
        return desired - e.get_velocity();
    }
    return {0, 0, 0};
}
