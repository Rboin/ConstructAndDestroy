//
// Created by robin on 3/21/17.
//

#include <SDL2/SDL_keycode.h>
#include <entity/static/building/building_manager.h>
#include "key_handler.h"


bool KeyHandler::handle(key_event_data data) {
    //110 = 'N'
    if (data.data == 110) {

        BuildingManager::get_instance()->add_building();
    }
    return false;
}
