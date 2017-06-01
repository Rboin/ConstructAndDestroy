//
// Created by Jeroen on 5/11/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_BUILDINGPANEL_H
#define CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_BUILDINGPANEL_H

#include "sdl/event/sdl_event_types.h"
#include "sdl/event/slot/sdl_mouse_event_slot.h"

class SDL_ImageRenderObject;
class SDLUnitPanel;

class MouseHandlerBuildingPanel : public SDL_MouseEventSlot {
private:
    void handle_up(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel);
    void handle(sdl_mouse_event_data, SDLUnitPanel *);
    void handle_motion(sdl_mouse_event_data data, SDLUnitPanel* sdl_panel);
public:
    MouseHandlerBuildingPanel();
    ~MouseHandlerBuildingPanel();
    void  on(sdl_mouse_event_data d) override;
};

#endif //CONSTRUCT_AND_DESTROY_MOUSE_HANDLER_BUILDINGPANEL_H
