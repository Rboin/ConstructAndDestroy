//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_OBSTACLE_AVOIDANCE_STRATEGY_H
#define C_AND_D_PROJECT_OBSTACLE_AVOIDANCE_STRATEGY_H

#include "behaviour_strategy.h"

class ObstacleAvoidanceStrategy : public BehaviourStrategy {
    vec2 calculate_force(MovingEntity &, std::vector<BaseEntity *>);
};

#endif //C_AND_D_PROJECT_OBSTACLE_AVOIDANCE_STRATEGY_H
