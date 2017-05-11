//
// Created by Sander on 4-4-2017.
//

#include "lumberjack_entity.h"
#include "sdl/image/sdl_image_render_object.h"

LumberJackEntity::LumberJackEntity(const mesh *base, vec2 position, float mass,
                                   const float max_force, const float max_speed) :
        MovingEntity(base, position, mass, max_force, max_speed, WOODCUTTER) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
}

void LumberJackEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_lumberjack.png"};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}

void LumberJackEntity::deselect() {
    sdl_image_data* entity_data = new sdl_image_data{"lumberjack.png"};
    this->representation->set_data(entity_data);
    this->representation->clear_data();

}