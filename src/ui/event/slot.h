//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SLOT_H
#define CONSTRUCT_AND_DESTROY_SLOT_H

#include <cstdint>
#include "types.h"

struct event_data {
    uint32_t type, timestamp;

    event_data(uint32_t ty, uint32_t time) {
        type = ty;
        timestamp = time;
    }
};

struct mouse_event_data : public event_data {
    const vec2 &position;

    mouse_event_data(uint32_t ty, uint32_t time, vec2 &pos) :
            event_data(ty, time),
            position(pos) {}
};

struct key_event_data : public event_data {
    char key;

    key_event_data(uint32_t ty, uint32_t time, char k) : event_data(ty, time), key(k) {}
};

template<typename T>
class Slot {
public:
    Slot() {}
    virtual void on(T) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_SLOT_H
