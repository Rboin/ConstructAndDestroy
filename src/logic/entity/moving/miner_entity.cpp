//
// Created by Sander on 4-4-2017.
//

#include "miner_entity.h"
#include <iostream>
#include <sdl/image/sdl_image_render_object.h>

extern const std::string path_to_texture;
extern const std::string path_to_selected_texture;

MinerEntity::MinerEntity(const mesh *base, vec2 position, float mass,
                         const float max_force, const float max_speed) :
        MovingEntity(base, position, mass, max_force, max_speed, MINER) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
    texture = "miner.png";

}

void MinerEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_" + texture};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}

void MinerEntity::deselect() {
    sdl_image_data* entity_data =  new sdl_image_data{texture};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}

std::string MinerEntity::get_texture() {
    return texture;
}

void MinerEntity::set_texture(std::string src) {
    texture = src;
}
