//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_FLEE_STRATEGY_H
#define C_AND_D_PROJECT_FLEE_STRATEGY_H

#include "behaviour/behaviour_strategy.h"

class FleeStrategy : public BehaviourStrategy {
public:
    vec2 calculate_force(MovingEntity &, std::vector<BaseEntity *>);
};

#endif //C_AND_D_PROJECT_FLEE_STRATEGY_H
