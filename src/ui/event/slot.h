//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SLOT_H
#define CONSTRUCT_AND_DESTROY_SLOT_H

template<typename T>
class Slot {
public:
    Slot() {}
    virtual void on(T) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_SLOT_H
