//
// Created by Jeroen on 5/11/2017.
//

#include "sdl_building_panel.h"
#include "settings.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl_unit_panel.h"

SDLBuildingPanel::SDLBuildingPanel(SDL_RenderObject *r) : SDLPanel(r) {
    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();

    // for each building that can be created
    // render one panel per building
    for (int i = 0; i < buildings_with_textures->size(); i++) {
        MouseHandlerBuildingPanel *slot = new MouseHandlerBuildingPanel();
        building_with_texture building = buildings_with_textures->at((unsigned int) i);

        vec2 pos = {(float) (100 * i), this->get_representation()->get_position()->clone().y};
        vec2 size = {100, 100};
        SDLUnitPanel *unit_panel = new SDLUnitPanel(building.texture, pos, size, building.type);
        unit_panel->set_mouse_callback(slot);
        mouse_dispatcher->register_callback(unit_panel, slot);

        this->add_component(unit_panel);
    }
}

void SDLBuildingPanel::render(SDLRenderer *renderer, float d) {
    SDLPanel::render(renderer, d);
}