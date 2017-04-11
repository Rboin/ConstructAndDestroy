//
// Created by robin on 3/1/17.
//

#include "obstacle_avoidance_strategy.h"
#include "entity/moving/moving_entity.h"

vec2 ObstacleAvoidanceStrategy::calculate_force(MovingEntity &e, std::vector<BaseEntity *> neighbourhood) {
    //todo:: set MAX_SEE_AHEAD in configuration file
    float max_see_ahead = 100;

    float min_distance;
    vec2 *result = NULL;
    for (int i = 0; i < _target_size; i++) {
        float dist = (e.get_position() - _targets[i]).length();
        if (!result || (dist < min_distance)) {
            min_distance = dist;
            result = &_targets[i];
        }
    }


    vec2 avoidance = {0, 0};
    if (result && min_distance < max_see_ahead) {
        avoidance = (e.get_position() + e.get_velocity() - *result).normalize();
    }

    return avoidance;
}
