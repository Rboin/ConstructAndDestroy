//
// Created by Sander on 7-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_RESEARCHPANEL_H
#define CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_RESEARCHPANEL_H


#include "sdl/panel/sdl_unit_panel.h"
#include "sdl/event/sdl_event_types.h"
#include "sdl/event/slot/sdl_mouse_event_slot.h"

class MouseHandlerResearchPanel : public SDL_MouseEventSlot {
private:
    void handle_up(SDLUnitPanel *sdl_panel);
    void handle(sdl_mouse_event_data, SDLUnitPanel *);
    void handle_motion(sdl_mouse_event_data data, SDLUnitPanel* sdl_panel);
public:
    MouseHandlerResearchPanel();
    ~MouseHandlerResearchPanel();
    void  on(sdl_mouse_event_data d) override;
};


#endif //CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_RESEARCHPANEL_H
