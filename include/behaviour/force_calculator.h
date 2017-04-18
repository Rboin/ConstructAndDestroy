//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_FORCE_CALCULATOR_H
#define C_AND_D_PROJECT_FORCE_CALCULATOR_H

#include <vector>
#include "types.h"

//=================== Forward declarations ===================
class BaseEntity;

class MovingEntity;

class BehaviourStrategy;
//============================================================

/**
 * The force calculator interface.
 * Can be inherited to create e.g. a weighted force calculator.
 */
class ForceCalculator {
public:
    /**
     * Method that calculates the total amount of force produced by the attached behaviours.
     * @return vec2 force
     */
    virtual vec2 calculate(MovingEntity &, std::vector<BehaviourStrategy *>, std::vector<BaseEntity *>) = 0;
};

#endif //C_AND_D_PROJECT_FORCE_CALCULATOR_H
