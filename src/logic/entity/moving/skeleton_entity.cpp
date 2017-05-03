//
// Created by Sander on 6-4-2017.
//

#include "skeleton_entity.h"
#include <iostream>
#include "../globals.cpp"
#include <sdl/image/sdl_image_render_object.h>

extern const std::string path_to_texture;
extern const std::string path_to_selected_texture;

SkeletonEntity::SkeletonEntity(const mesh *base, vec2 position, float mass,
                               const float max_force, const float max_speed) :
        MovingEntity(base, position, mass,
                     max_force,
                     max_speed, ENEMY) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
//    texture_path = "axe.png";
}

void SkeletonEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_axe.png"};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}

void SkeletonEntity::deselect() {
    sdl_image_data* entity_data =  new sdl_image_data{"axe.png"};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}