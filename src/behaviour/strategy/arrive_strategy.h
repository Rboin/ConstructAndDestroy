//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_ARRIVESTRATEGY_H
#define C_AND_D_PROJECT_ARRIVESTRATEGY_H

#include "behaviour/behaviour_strategy.h"

class ArriveStrategy : public BehaviourStrategy {
public:
    vec2 calculate_force(MovingEntity &, std::vector<BaseEntity *>);
};

#endif //C_AND_D_PROJECT_ARRIVESTRATEGY_H
