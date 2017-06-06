//
// Created by Mark on 6-6-2017.
//

#include <types.h>
#include "sdl/image/sdl_image_render_object.h"
#include "mercenary_entity.h"


MercenaryEntity::MercenaryEntity(vec2 position, float mass,
                                   const float max_force, const float max_speed) :
        MovingEntity(position, mass, max_force, max_speed, ENEMY) {
    carrying = 0;
    _attack_damage = 12;
    texture = "mercenary.png";
}

void MercenaryEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_" + texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


void MercenaryEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


std::string MercenaryEntity::get_texture() {
    return texture;
}

void MercenaryEntity::set_texture(std::string src) {
    this->texture = src;
}