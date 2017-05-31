//
// Created by robin on 3/1/17.
//

#include <vector>
#include "behaviour/behaviour.h"
#include "vector.h"
#include "behaviour/force_calculator.h"
#include "behaviour/behaviour_strategy.h"

Behaviour::Behaviour(ForceCalculator *fc) {
    _calculator = fc;
    _behaviours = std::map<int, BehaviourStrategy *>();
}

Behaviour::~Behaviour() {
    if(_calculator){
        delete _calculator;
    }
    remove_all();
}

void Behaviour::add(int type, BehaviourStrategy *s) {
    _behaviours.insert(std::make_pair(type, s));
}

void Behaviour::remove(int type) {
    if (_behaviours[type]) {
        BehaviourStrategy *strategy = _behaviours[type];
        _behaviours.erase(type);
        delete strategy;
    }
}

void Behaviour::set_target_for(int type, vec2 *v, int target_size) {
    if (_behaviours[type])
        _behaviours[type]->set_targets(v, target_size);
}

vec2 Behaviour::calculate_force(MovingEntity &entity) {
    std::vector<BehaviourStrategy *> strategies;
    for (std::map<int, BehaviourStrategy *>::iterator it = _behaviours.begin();
         it != _behaviours.end(); it++) {

        strategies.push_back(it->second);
    }
    return _calculator->calculate(entity, strategies);
}

bool Behaviour::has_behaviour(int type) {
    return _behaviours[type] != NULL;
}

void Behaviour::remove_all() {
    for (std::map<int, BehaviourStrategy *>::iterator it = _behaviours.begin(); it != _behaviours.end(); it++) {
        delete (it->second);
    }
    _behaviours.clear();
}

