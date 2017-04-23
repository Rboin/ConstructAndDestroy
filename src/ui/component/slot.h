//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SLOT_H
#define CONSTRUCT_AND_DESTROY_SLOT_H

template<typename T>
struct event {
    T data;
};

template<typename T>
class Slot {
public:
    virtual void on(event<T>) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_SLOT_H
