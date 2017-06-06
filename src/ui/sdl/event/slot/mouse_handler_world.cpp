//
// Created by Mark on 1-5-2017.
//

#include "settings.h"
#include <cmath>
#include <iostream>
#include "mouse_handler_world.h"
#include "settings.h"
#include "world/world.h"
#include "entity/player.h"
#include "behaviour/move_order.h"
#include "camera/camera_manager.h"
#include <iostream>
#include "sdl/event/sdl_event_types.h"

#include "entity/static/building/building_state/placing_building.h"
#include "entity/static/building/building_state/choosing_building_position.h"
#include "state/state_machine.h"
#include "entity/moving/moving_entity_manager.h"
#include "sdl/panel/sdl_world_panel.h"
#include "entity/moving/moving_entity_factory.h"
#include "entity/player_manager.h"

MouseHandlerWorld::MouseHandlerWorld() {
    start_drag_x = -1;
    start_drag_y = -1;
}

MouseHandlerWorld::~MouseHandlerWorld() {}


void MouseHandlerWorld::handle_down(sdl_mouse_event_data data, SDLWorldPanel *world_panel) {
    start_world = CameraManager::to_world(data.position);
    start_drag_x = (int)data.position.x;
    start_drag_y = (int)data.position.y;
    world_panel->start_drag.x =  data.position.x;
    world_panel->start_drag.y =  data.position.y;
}

void MouseHandlerWorld::handle_up(sdl_mouse_event_data data) {
    Player* player = PlayerManager::get_instance()->get_player(player_id);

    // if the player is in the ChoosingBuildingPosition state, change state to placing building
    if (dynamic_cast<ChoosingBuildingPosition*>(player->state_machine->current_state)) {
        player->state_machine->change_state(new PlacingBuilding());
    } else {
        //check if event is a click or a drag.
        if (std::abs(start_drag_x - data.position.x) < 10 && std::abs(start_drag_y - data.position.y) < 10) {
            //it is a click
            vec2 pos = CameraManager::to_world(data.position);
            player->select_one_unit(pos);

            if (player->selected_units.empty()) {
                player->select_building(pos);
            }

        } else {
            //it is a drag.
            player->select_units_in_rectangle(start_world.x, start_world.y,
                                              end_world.x, end_world.y);
        }
    }
}


void MouseHandlerWorld::on(sdl_mouse_event_data data) {
    SDLWorldPanel *world_panel = (SDLWorldPanel *) data.component;
    if (data.type == SDL_MOUSEMOTION) {
        handle_motion(data, world_panel);
    }
    else if( data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP){
        handle(data, world_panel);
    } else if(data.type == SDL_MOUSEWHEEL) {
        handle_mouse_scroll(data);
    }
}

void MouseHandlerWorld::handle_motion(sdl_mouse_event_data data, SDLWorldPanel *world_panel) {
    if(data.button == SDL_BUTTON_LEFT){
        end_world = CameraManager::to_world(data.position);
        world_panel->dragging = true;
        world_panel->end_drag.x = data.position.x;
        world_panel->end_drag.y =  data.position.y;
    }
}

void MouseHandlerWorld::handle(sdl_mouse_event_data data, SDLWorldPanel *world_panel) {
    vec2 pos = CameraManager::to_world(data.position);

    switch(data.button) {
        case SDL_BUTTON_LEFT:
            if (data.type == SDL_MOUSEBUTTONDOWN) {
                return handle_down(data, world_panel);
            } else if (data.type == SDL_MOUSEBUTTONUP) {
                //reset drag variables before handling event
                world_panel->dragging = false;
                world_panel->start_drag.x = -1;
                world_panel->start_drag.y = -1;
                return handle_up(data);
            }

            return;

        case SDL_BUTTON_RIGHT:
            if (data.type == SDL_MOUSEBUTTONDOWN) {
                return handle_right_button(data, pos);
            }

        default:
            return;
    }
}

void MouseHandlerWorld::handle_right_button(sdl_mouse_event_data &data, const vec2 &v) {
    MoveOrder::get_instance()->orderMove(&PlayerManager::get_instance()->get_player(player_id)->selected_units, v);
}

void MouseHandlerWorld::handle_mouse_scroll(sdl_mouse_event_data &data) {
    // Using the button variable as the direction of the scroll,
    // which is 1 for scroll up, and -1 for scroll down.
    CameraManager::get_instance()->zoom(camera_initial_scroll_speed * data.button);
}

