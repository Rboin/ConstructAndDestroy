#ifndef CONSTRUCT_AND_DESTROY_MOVE_ORDER_H
#define CONSTRUCT_AND_DESTROY_MOVE_ORDER_H

#include <vector>
#include "vector.h"

class MovingEntity;
class OrderStrategy;

class MoveOrder {
private:
    static MoveOrder *_instance;
    std::vector<OrderStrategy*> _strategies;
    MoveOrder();
public:
    ~MoveOrder();
    void orderMove(std::vector<MovingEntity *>* units, vec2 targetVector);

    static MoveOrder *get_instance();
};


#endif //CONSTRUCT_AND_DESTROY_MOVE_ORDER_H
