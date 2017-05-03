#include "order_strategy.h"

bool OrderStrategy::applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    // is overridden by the inheriting strategies
    return false;
}

void OrderStrategy::execute(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    // is overridden by the inheriting strategies
}
