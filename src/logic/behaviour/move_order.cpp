#include <neighbourhood/neighbourhood_manager.h>
#include <behaviour/orderstrategies/default_order_strategy.h>
#include "move_order.h"
#include "orderstrategies/ground_order_strategy.h"
#include "orderstrategies/lumber_order_strategy.h"

MoveOrder *MoveOrder::_instance = nullptr;

void MoveOrder::orderMove(std::vector<MovingEntity *> *units, vec2 targetVector) {
    BaseEntity *target = NeighbourhoodManager::get_instance()->get_closest_to(targetVector);

    for(int i = 0; i < strategies.size(); i++) {
        if (strategies.at(i)->applies(units, targetVector, target)) {
            strategies.at(i)->execute(units, targetVector, target);
        }
    }
}

MoveOrder::MoveOrder() {
    strategies = {
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
    for(int i = 0; i < strategies.size(); i++) {
        delete strategies.at(i);
    }
}