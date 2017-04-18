//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_BASIC_FORCE_CALCULATOR_H
#define C_AND_D_PROJECT_BASIC_FORCE_CALCULATOR_H

#include "behaviour/force_calculator.h"

class BasicForceCalculator : public ForceCalculator {

public:
    vec2 calculate(MovingEntity &, std::vector<BehaviourStrategy *>, std::vector<BaseEntity *>);
};

#endif //C_AND_D_PROJECT_BASIC_FORCE_CALCULATOR_H
