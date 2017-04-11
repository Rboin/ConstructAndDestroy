//
// Created by robin on 3/1/17.
//

#include "flee_strategy.h"
#include "entity/moving/moving_entity.h"

vec2 FleeStrategy::calculate_force(MovingEntity &e, std::vector<BaseEntity *> neighbourhood) {
    float panic_distance = 150 * 150;
    float distance = e.get_position().distance_squared(*_targets);

    if (distance > panic_distance) {
        return vec2{0, 0, 0};
    }

    return ((e.get_position() - *_targets).normalize() * e.get_max_speed()) - e.get_velocity();
}
