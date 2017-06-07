//
// Created by Mark on 6-6-2017.
//

#include <types.h>
#include "sdl/image/sdl_image_render_object.h"
#include "heavy_cavalier_entity.h"
#include "entity/upgrade_manager.h"

HeavyCavalierEntity::HeavyCavalierEntity(vec2 position, float mass) :
        MovingEntity(position, mass, ENEMY) {
    carrying = 0;
    max_force = 0.2;
    max_speed = 0.2;
    _attack_damage = 15 * UpgradeManager::get_instance()->extra_damage;
    _max_health = 225 * UpgradeManager::get_instance()->extra_hp;
    _health = 225 * UpgradeManager::get_instance()->extra_hp;
    texture = "heavycavalier.png";
}

void HeavyCavalierEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


void HeavyCavalierEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}

std::string HeavyCavalierEntity::get_texture() {
    return texture;
}

void HeavyCavalierEntity::set_texture(std::string src) {
    this->texture = src;
}