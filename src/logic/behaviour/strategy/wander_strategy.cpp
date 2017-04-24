//
// Created by Sander on 1-3-2017.
//

#include <cmath>
#include "types.h"
#include "entity/moving/moving_entity.h"
#include "wander_strategy.h"

vec2 WanderStrategy::calculate_force(MovingEntity &e, std::vector<BaseEntity *> neighbourhood) {
    //calculate the circle center
    vec2 circle_center;
    circle_center = e.get_velocity();
    circle_center.normalize();
    circle_center *= circle_distance;

    //calculate the displacement force
    vec2 displacement_force = {0, -1};
    displacement_force *= circle_radius;

    //randomly change the vector direction by changing the angle.
    set_angle(displacement_force, wander_angle);
    float angle_change = 1;
    wander_angle += rand() % 2 * angle_change - angle_change * 0.5;

    //calculate and return wander force
    vec2 wander_force = circle_center + displacement_force;
    return wander_force;
}

void WanderStrategy::set_angle(vec2 &vector, float number) {
    float len = vector.length();
    vector.x = cos(number) * len;
    vector.y = sin(number) * len;
}
