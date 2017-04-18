//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_BEHAVIOUR_H
#define C_AND_D_PROJECT_BEHAVIOUR_H

#include <map>
#include "types.h"

//=================== Forward declarations ===================
class ForceCalculator;

class BehaviourStrategy;

class BaseEntity;

class MovingEntity;
//============================================================

/**
 * The behaviour aggregate class. This class is an aggregate of a calculator, and different behaviours.
 */
class Behaviour {
private:
    ForceCalculator *_calculator;
    std::map<int, BehaviourStrategy *> _behaviours;

public:
    Behaviour(ForceCalculator *);

    void add(int, BehaviourStrategy *);

    void remove(int);

    void set_target_for(int, vec2 *, int);

    bool has_behaviour(int);

    vec2 calculate_force(MovingEntity &, std::vector<BaseEntity *>);
};

#endif //C_AND_D_PROJECT_BEHAVIOUR_H
