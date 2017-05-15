//
// Created by Sander on 6-4-2017.
//

#include <iostream>
#include "skeleton_entity.h"
#include "sdl/image/sdl_image_render_object.h"

extern const std::string path_to_texture;

SkeletonEntity::SkeletonEntity(const mesh *base, vec2 position, float mass,
                               const float max_force, const float max_speed) :
        MovingEntity(base, position, mass,
                     max_force,
                     max_speed, ENEMY) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
    texture = "axe.png";
}

void SkeletonEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_" + texture};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}

void SkeletonEntity::deselect() {
    sdl_image_data* entity_data =  new sdl_image_data{texture};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}

std::string SkeletonEntity::get_texture() {
    return texture;
}

void SkeletonEntity::set_texture(std::string src) {
    texture = src;
}
