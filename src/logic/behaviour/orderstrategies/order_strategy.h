#ifndef CONSTRUCT_AND_DESTROY_ORDER_STRATEGY_BASE_H
#define CONSTRUCT_AND_DESTROY_ORDER_STRATEGY_BASE_H

#include <vector>
#include "types.h"

class MovingEntity;
class BaseEntity;

class OrderStrategy {
public:
    virtual bool applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target);
    virtual void execute(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target);
};


#endif //CONSTRUCT_AND_DESTROY_ORDER_STRATEGY_BASE_H
