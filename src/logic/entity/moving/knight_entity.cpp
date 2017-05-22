//
// Created by Stephan Schrijver on 9-5-2017.
//
#include <iostream>
#include "sdl/image/sdl_image_render_object.h"
#include "knight_entity.h"

KnightEntity::KnightEntity(const mesh *base, vec2 position, float mass,
                                   const float max_force, const float max_speed) :
        MovingEntity(base, position, mass, max_force, max_speed, ENEMY) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
    _attack_damage = 8;
    texture = "knight.png";
}

void KnightEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_" + texture};
    representation->set_data(entity_data);
    representation->clear_data();
}


void KnightEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    representation->set_data(entity_data);
    representation->clear_data();
}

std::string KnightEntity::get_texture() {
    std::cout << texture << std::endl;
    return texture;
}

void KnightEntity::set_texture(std::string src) {
    this->texture = src;
}

