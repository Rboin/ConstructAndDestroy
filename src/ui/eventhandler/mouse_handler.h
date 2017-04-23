//
// Created by Sander on 23-3-2017.
//

#ifndef C_AND_D_PROJECT_MOUSE_EVENT_HANDLER_H
#define C_AND_D_PROJECT_MOUSE_EVENT_HANDLER_H


#include <SDL_events.h>
#include "types.h"
#include "observer/observable.h"
#include "event_handler.h"

class Graph;

class MovingEntity;

struct mouse_event_data : public event_data<SDL_MouseButtonEvent> {
    Graph *graph;
};

class MouseHandler : public EventHandler<mouse_event_data>, public Observable<MovingEntity *> {
private:
    const bool handle_left_button(const vec2 &);

    const bool handle_right_button(mouse_event_data &, const vec2 &);

public:
    bool handle(mouse_event_data data) override;
};


#endif //C_AND_D_PROJECT_MOUSE_EVENT_HANDLER_H
