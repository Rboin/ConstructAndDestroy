//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_BEHAVIOUR_STRATEGY_H
#define C_AND_D_PROJECT_BEHAVIOUR_STRATEGY_H

#include <vector>
#include "types.h"

//=================== Forward declarations ===================
class BaseEntity;
class MovingEntity;
//============================================================

/**
 * The base behaviour class, from which the other behaviours van be derived.
 */
class BehaviourStrategy {
protected:
    vec2 *_targets;
    int _target_size;
public:
    void set_targets(vec2 *, int size = 1);

    ~BehaviourStrategy();
    /**
     * Method that calculates the amount of force for our given entity.
     * @return
     */
    virtual vec2 calculate_force(MovingEntity &) = 0;
};

#endif //C_AND_D_PROJECT_BEHAVIOUR_STRATEGY_H
