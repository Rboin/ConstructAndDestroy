//
// Created by Mark on 6-6-2017.
//

#include <types.h>
#include "sdl/image/sdl_image_render_object.h"
#include "light_cavalier.h"

LightCavalierEntity::LightCavalierEntity(vec2 position, float mass) :
        MovingEntity(position, mass, ENEMY) {
    carrying = 0;
    max_force = 0.2;
    max_speed = 0.2;
    _attack_damage = 5;
    _max_health = 150;
    _health = 150;
    texture = "lightcavalier.png";
}

void LightCavalierEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


void LightCavalierEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}

std::string LightCavalierEntity::get_texture() {
    return texture;
}

void LightCavalierEntity::set_texture(std::string src) {
    this->texture = src;
}