//
// Created by robin on 3/1/17.
//

#include "vector.h"
#include "basic_force_calculator.h"
#include "behaviour/behaviour_strategy.h"

vec2 BasicForceCalculator::calculate(MovingEntity &entity,
                                     std::vector<BehaviourStrategy *> strategies) {

    vec2 force = {0, 0, 0};
    if (strategies.size() > 0) {
        for (unsigned int i = 0; i < strategies.size(); i++) {
            if (strategies.at(i) != 0)
                force += strategies.at(i)->calculate_force(entity);
        }
    }
    return force;
}
