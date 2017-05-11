//
// Created by Stephan Schrijver on 9-5-2017.
//
#include "sdl/image/sdl_image_render_object.h"
#include "knight_entity.h"

KnightEntity::KnightEntity(const mesh *base, vec2 position, float mass,
                                   const float max_force, const float max_speed) :
        MovingEntity(base, position, mass, max_force, max_speed, WOODCUTTER) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
}

void KnightEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_knight.png"};
    representation->set_data(entity_data);
    representation->clear_data();
}

void KnightEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{"knight.png"};
    representation->set_data(entity_data);
    representation->clear_data();
}
