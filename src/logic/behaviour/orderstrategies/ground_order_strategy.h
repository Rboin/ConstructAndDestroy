#ifndef CONSTRUCT_AND_DESTROY_GROUND_ORDER_STRATEGY_H
#define CONSTRUCT_AND_DESTROY_GROUND_ORDER_STRATEGY_H

#include "order_strategy.h"
class MovingEntity;
class BaseEntity;

class GroundOrderStrategy : public OrderStrategy {
public:
    bool applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target);
    void execute(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target);
};

#endif //CONSTRUCT_AND_DESTROY_GROUND_ORDER_STRATEGY_H
