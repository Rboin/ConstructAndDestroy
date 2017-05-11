//
// Created by Mark on 1-5-2017.
//

#include "mouse_handler_world.h"
#include "world/world.h"
#include "cmath"
#include "entity/player.h"
#include "behaviour/move_order.h"
#include <iostream>
#include "entity/player_manager.h"
#include "sdl/panel/sdl_world_panel.h"
#include "../globals.cpp"

MouseHandlerWorld::MouseHandlerWorld() {
    start_drag_x = -1;
    start_drag_y = -1;
}

MouseHandlerWorld::~MouseHandlerWorld() {}


void MouseHandlerWorld::handle_down(sdl_mouse_event_data data, SDLWorldPanel *world_panel) {
    start_drag_x = data.position.x;
    start_drag_y = data.position.y;
    world_panel->start_drag.x =  data.position.x;
    world_panel->start_drag.y =  data.position.y;
}

void MouseHandlerWorld::handle_up(sdl_mouse_event_data data) {
    //check if event is a click or a drag.
    if(std::abs(start_drag_x - data.position.x) < 10 &&  std::abs(start_drag_y - data.position.y) < 10){
        //it is a click
        vec2 pos = {(float) data.position.x, (float) data.position.y};
        PlayerManager::get_instance()->get_player(1)->select_one_unit(pos);

    } else {
        //it is a drag.
        PlayerManager::get_instance()->get_player(player_id)->select_units_in_rectangle(start_drag_x, start_drag_y, data.position.x, data.position.y);
    }
}


void MouseHandlerWorld::on(sdl_mouse_event_data data) {
    SDLWorldPanel *world_panel = (SDLWorldPanel *) data.component;
    if (data.type == SDL_MOUSEMOTION) {
        handle_motion(data, world_panel);
    }
    else if( data.type == SDL_MOUSEBUTTONDOWN || data.type == SDL_MOUSEBUTTONUP){
        handle(data, world_panel);
    }
}

void MouseHandlerWorld::handle_motion(sdl_mouse_event_data data, SDLWorldPanel *world_panel) {
    if(data.button == SDL_BUTTON_LEFT){
        world_panel->dragging = true;
        world_panel->end_drag.x = data.position.x;
        world_panel->end_drag.y =  data.position.y;
    }

}

void MouseHandlerWorld::handle(sdl_mouse_event_data data, SDLWorldPanel *world_panel) {
    vec2 pos = data.position;

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

