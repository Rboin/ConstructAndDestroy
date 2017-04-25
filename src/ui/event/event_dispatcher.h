//
// Created by robin on 4/25/17.
//

#ifndef CONSTRUCT_AND_DESTROY_EVENT_DISPATCHER_H
#define CONSTRUCT_AND_DESTROY_EVENT_DISPATCHER_H

#include <map>
#include <vector>
#include "slot.h"

/**
 * @tparam T = Type of object, i.e UIComponent.
 * @tparam D = Type of data that gets sent to the given Slot object
 */
template<typename T, typename D>
class EventDispatcher {
protected:
    std::map<T *, Slot<D> *> _registered_slots;
public:
    EventDispatcher() : _registered_slots(std::map<T *, Slot<D> *>()) {}

    /**
     * Registers a Slot object which contains a callback function.
     * @param instance
     * @param s
     */
    void register_callback(T *instance, Slot<D> *s) {
        _registered_slots[instance] = s;
    }

    /**
     * Determines to which object we need to send the event and calls that object's callback function.
     * @param d
     */
    virtual void dispatch(D) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_EVENT_DISPATCHER_H
