//
// Created by Jeroen on 5/18/2017.
//

#include "mouse_handler_entitypanel.h"
#include <entity/player_manager.h>
#include <entity/static/building/building_state/choosing_building_position.h>
#include <entity/static/building/building_state/placing_building.h>
#include <entity/static/building/building_manager.h>
#include <sdl/progressbar/sdl_progressbar_render_object.h>
#include <sdl/panel/sdl_progressbar_panel.h>
#include "mouse_handler_buildingpanel.h"
#include "world/world.h"
#include "entity/player.h"
#include "settings.h"
#include "state/state_machine.h"

MouseHandlerEntityPanel::MouseHandlerEntityPanel() {
}

MouseHandlerEntityPanel::~MouseHandlerEntityPanel() {}

void MouseHandlerEntityPanel::handle_up(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    Player *p = PlayerManager::get_instance()->get_player(player_id);

    BuildingEntity* building = sdl_panel->get_building_entity();

    if (p->resources->check_if_sufficient_resources(building->get_costs())) {
        SpawnableEntity* spawnable_entity = sdl_panel->get_spawnable_entity();

        // tell the building to spawn the selected entity type
        building->order_unit(spawnable_entity->get_entity_type());


        // create a progressbarpanel at the center of the unit panel
        // indicating how long it will take to spawn the selected unit
        const vec2* parent_size = sdl_panel->get_size();
        const vec2* parent_pos = sdl_panel->get_position();
        vec2 pb_panel_pos = {parent_pos->x + (parent_size->x / 2 - 15.0), parent_pos->y + (parent_size->y / 2 - 2.5)}, pb_panel_size = {30, 5};
        sdl_data pb_panel_data = {0, 0, 0, 0};
        SDL_ProgressbarRenderObject* panel_pb = new SDL_ProgressbarRenderObject(pb_panel_pos, pb_panel_size, { 255, 255, 255, 255}, &pb_panel_data);
        SDLProgressBarPanel* pb_panel = new SDLProgressBarPanel(panel_pb, building->get_order_time(), sdl_panel);
        sdl_panel->add_component(pb_panel);

        // remove resources from the player
        p->resources->subtract_resources(spawnable_entity->get_cost());
    }
}


void MouseHandlerEntityPanel::on(sdl_mouse_event_data data) {
    SDLUnitPanel *sdl_panel = (SDLUnitPanel *) data.component;
    if( data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP){
        handle(data, sdl_panel);
    }
}

void MouseHandlerEntityPanel::handle(sdl_mouse_event_data data, SDLUnitPanel *sdl_panel) {
    vec2 pos = data.position;

    switch(data.button) {
        case SDL_BUTTON_LEFT:
            if (data.type == SDL_MOUSEBUTTONUP) {
                return handle_up(data, sdl_panel);
            }

            return;

        default:
            return;
    }
}