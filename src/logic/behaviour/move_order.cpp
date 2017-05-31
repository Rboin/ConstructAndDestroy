#include "behaviour/orderstrategies/default_order_strategy.h"
#include "world/world.h"
#include "move_order.h"
#include "orderstrategies/lumber_order_strategy.h"

MoveOrder *MoveOrder::_instance = nullptr;

void MoveOrder::orderMove(std::vector<MovingEntity *> *units, vec2 targetVector) {
    BaseEntity *target = World::get_instance()->get_closest_to(targetVector);

    for(int i = 0; i < _strategies.size(); i++) {
        if (_strategies.at(i)->applies(units, targetVector, target)) {
            _strategies.at(i)->execute(units, targetVector, target);
        }
    }
}

MoveOrder::MoveOrder() {
    _strategies = {
            new GroundOrderStrategy(),
            new LumberOrderStrategy(),
            new DefaultOrderStrategy(),
    };
}

MoveOrder *MoveOrder::get_instance() {
    if (_instance == nullptr)
        _instance = new MoveOrder();
    return _instance;
}

MoveOrder::~MoveOrder() {
    for(int i = 0; i < _strategies.size(); i++) {
        delete _strategies.at(i);
    }
    _instance = nullptr;
}