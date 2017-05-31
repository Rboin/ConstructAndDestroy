//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_SEEK_STRATEGY_H
#define C_AND_D_PROJECT_SEEK_STRATEGY_H

#include "behaviour/behaviour_strategy.h"

class SeekStrategy : public BehaviourStrategy {
public:
    vec2 calculate_force(MovingEntity &);
};

#endif //C_AND_D_PROJECT_SEEK_STRATEGY_H
