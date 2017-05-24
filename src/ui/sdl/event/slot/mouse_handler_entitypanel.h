//
// Created by Jeroen on 5/18/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_ENTITYPANEL_H
#define CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_ENTITYPANEL_H

#include "sdl/event/slot/sdl_mouse_event_slot.h"

class SDLUnitPanel;

class MouseHandlerEntityPanel : public SDL_MouseEventSlot {
private:
    void handle_up(SDLUnitPanel *sdl_panel);
    void handle(sdl_mouse_event_data, SDLUnitPanel *);
public:
    MouseHandlerEntityPanel();
    ~MouseHandlerEntityPanel();
    void  on(sdl_mouse_event_data d) override;
};

#endif //CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_ENTITYPANEL_H
