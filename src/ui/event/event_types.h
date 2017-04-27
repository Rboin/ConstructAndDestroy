//
// Created by robin on 4/26/17.
//

#ifndef CONSTRUCT_AND_DESTROY_EVENT_TYPES_H
#define CONSTRUCT_AND_DESTROY_EVENT_TYPES_H

#include <cstdint>
#include "types.h"

struct event_data {
    uint32_t type, timestamp;

    event_data(uint32_t ty, uint32_t time) {
        type = ty;
        timestamp = time;
    }
};

template<typename T>
struct mouse_event_data : public event_data {
    const vec2 &position;
    T *component;

    mouse_event_data(uint32_t ty, uint32_t time, vec2 &pos) :
            event_data(ty, time),
            position(pos) {
        component = nullptr;
    }
};

struct key_event_data : public event_data {
    char key;

    key_event_data(uint32_t ty, uint32_t time, char k) : event_data(ty, time), key(k) {}
};
#endif //CONSTRUCT_AND_DESTROY_EVENT_TYPES_H
