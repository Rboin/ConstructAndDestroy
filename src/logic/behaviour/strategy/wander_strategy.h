//
// Created by Sander on 1-3-2017.
//

#ifndef C_AND_D_PROJECT_WANDER_STRATEGY_H
#define C_AND_D_PROJECT_WANDER_STRATEGY_H

#include "behaviour/behaviour_strategy.h"

class WanderStrategy : public BehaviourStrategy {
private:
    float wander_angle = 1;
    const float circle_distance = 5;
    const float circle_radius = 0.25; //increasing this number will lead to sharper turns.

public:
    vec2 calculate_force(MovingEntity &, std::vector<BaseEntity *>);

    void set_angle(vec2 &, float);
};

#endif //C_AND_D_PROJECT_WANDER_STRATEGY_H
