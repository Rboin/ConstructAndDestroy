//
// Created by robin on 3/1/17.
//

#include "seek_strategy.h"
#include "entity/moving/moving_entity.h"

vec2 SeekStrategy::calculate_force(MovingEntity &e) {
    if(_targets)
    return ((*_targets - e.get_position()).normalize() * e.get_max_speed()) - e.get_velocity();
}
