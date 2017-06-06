//
// Created by Mark on 6-6-2017.
//

#include <types.h>
#include "sdl/image/sdl_image_render_object.h"
#include "mercenary_entity.h"


MercenaryEntity::MercenaryEntity(vec2 position, float mass) :
        MovingEntity(position, mass, ENEMY) {
    carrying = 0;
    max_force = 0.2;
    max_speed = 0.1;
    _attack_damage = 20;
    _max_health = 50;
    _health = 50;
    texture = "mercenary.png";
}

void MercenaryEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
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