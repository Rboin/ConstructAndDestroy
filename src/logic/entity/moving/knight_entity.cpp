//
// Created by Stephan Schrijver on 9-5-2017.
//
#include <iostream>
#include "sdl/image/sdl_image_render_object.h"
#include "knight_entity.h"

KnightEntity::KnightEntity(vec2 position, float mass) :
        MovingEntity(position, mass, ENEMY) {
    carrying = 0;
    max_force = 0.2;
    max_speed = 0.1;
    _attack_damage = 7.5;
    _max_health = 125;
    _health = 125;
    texture = "knight.png";
}

void KnightEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


void KnightEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}

std::string KnightEntity::get_texture() {
    return texture;
}

void KnightEntity::set_texture(std::string src) {
    this->texture = src;
}

