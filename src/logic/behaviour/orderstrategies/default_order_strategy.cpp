//
// Created by Jeroen on 5/4/2017.
//

#include "default_order_strategy.h"

bool DefaultOrderStrategy::applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    // since this is the fallback strategy (the last strategy that will be evaluated), it should always be executed
    return true;
}