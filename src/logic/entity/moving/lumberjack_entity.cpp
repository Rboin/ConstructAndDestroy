//
// Created by Sander on 4-4-2017.
//

#include "lumberjack_entity.h"
#include "sdl/image/sdl_image_render_object.h"
#include <iostream>
#include <cmath>

LumberJackEntity::LumberJackEntity(vec2 position, float mass) :
        MovingEntity(position, mass, WOODCUTTER) {
    carrying = 0;
    texture = "lumberjack.png";
    max_force = 0.2;
    max_speed = 0.1;
}

void LumberJackEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

void LumberJackEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();

}

std::string LumberJackEntity::get_texture() {
    return texture;
}

void LumberJackEntity::set_texture(std::string src) {
    this->texture = src;
}

void LumberJackEntity::render(SDLRenderer *renderer, const mat2 &mat) {
    upsert_attribute("log.png", this->get_carrying());
    MovingEntity::render(renderer, mat);
}
