//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_EVENT_DISPATCHER_H
#define CONSTRUCT_AND_DESTROY_EVENT_DISPATCHER_H

template<typename T>
class EventDispatcher {
public:
    virtual void dispatch(T) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_EVENT_DISPATCHER_H
