//
// Created by Mark on 1-6-2017.
//

#include <types.h>
#include "sdl/image/sdl_image_render_object.h"
#include "cavalier_entity.h"
#include "entity/upgrade_manager.h"


CavalierEntity::CavalierEntity(vec2 position, float mass) :
        MovingEntity(position, mass, ENEMY) {
    carrying = 0;
    max_force = 0.2;
    max_speed = 0.2;
    _attack_damage = 10 * UpgradeManager::get_instance()->extra_damage;
    _max_health = 200 * UpgradeManager::get_instance()->extra_hp;
    _health = 200 * UpgradeManager::get_instance()->extra_hp;
    texture = "cavalier.png";

}

void CavalierEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


void CavalierEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}

std::string CavalierEntity::get_texture() {
    return texture;
}

void CavalierEntity::set_texture(std::string src) {
    this->texture = src;
}