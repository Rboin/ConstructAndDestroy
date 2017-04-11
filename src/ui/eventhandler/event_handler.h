//
// Created by robin on 3/21/17.
//

#ifndef C_AND_D_PROJECT_EVENT_HANDLER_H
#define C_AND_D_PROJECT_EVENT_HANDLER_H

template<typename T>
struct event_data {
    T data;
};

template<typename T>
class EventHandler {
public:
    virtual bool handle(T) = 0;
};

#endif //C_AND_D_PROJECT_EVENT_HANDLER_H
