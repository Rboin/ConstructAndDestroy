//
// Created by Jeroen on 5/4/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_DEFAULT_ORDER_STRATEGY_H
#define CONSTRUCT_AND_DESTROY_DEFAULT_ORDER_STRATEGY_H

#include "ground_order_strategy.h"
class MovingEntity;
class BaseEntity;

class DefaultOrderStrategy : public GroundOrderStrategy {
public:
    bool applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target);
};


#endif //CONSTRUCT_AND_DESTROY_DEFAULT_ORDER_STRATEGY_H
