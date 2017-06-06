//
// Created by Mark on 1-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_WORLD_H
#define CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_WORLD_H

#include "sdl/event/slot/sdl_mouse_event_slot.h"

class SDLWorldPanel;

class MouseHandlerWorld : public SDL_MouseEventSlot {
private:
    void handle_up(sdl_mouse_event_data data);
    void handle_down(sdl_mouse_event_data data, SDLWorldPanel *);
    void handle(sdl_mouse_event_data, SDLWorldPanel *);
    void handle_motion(sdl_mouse_event_data, SDLWorldPanel *);

    void handle_right_button(sdl_mouse_event_data &, const vec2 &);

    int start_drag_x;
    int start_drag_y;

    vec2 start_world, end_world;
public:
    MouseHandlerWorld();
    ~MouseHandlerWorld();
    void  on(sdl_mouse_event_data d) override;

    void handle_mouse_scroll(sdl_mouse_event_data &);
};

#endif //CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_WORLD_H
