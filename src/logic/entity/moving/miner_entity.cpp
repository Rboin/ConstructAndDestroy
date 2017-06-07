//
// Created by Sander on 4-4-2017.
//

#include <iostream>
#include "miner_entity.h"
#include "sdl/image/sdl_image_render_object.h"

MinerEntity::MinerEntity(vec2 position, float mass, const JobType jt) :
        MovingEntity(position, mass, jt) {
    carrying = 0;
    texture = "miner.png";
    max_force = 0.2;
    max_speed = 0.1;
}

void MinerEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

void MinerEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

std::string MinerEntity::get_texture() {
    return texture;
}

void MinerEntity::set_texture(std::string src) {
    texture = src;
}

void MinerEntity::render(SDLRenderer *renderer, const mat2 &mat) {
    if (get_job_type() == JobType::STONEMINER) {
        upsert_attribute("stone.png", this->get_carrying());
    } else if (get_job_type() == JobType::GOLDMINER) {
        upsert_attribute("gold.png", this->get_carrying());
    }
    MovingEntity::render(renderer, mat);
}
