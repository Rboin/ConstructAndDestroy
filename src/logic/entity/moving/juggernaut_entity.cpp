//
// Created by Mark on 6-6-2017.
//

#include <types.h>
#include "entity/upgrade_manager.h"
#include "sdl/image/sdl_image_render_object.h"
#include "juggernaut_entity.h"


JuggernautEntity::JuggernautEntity(vec2 position, float mass) :
        MovingEntity(position, mass, ENEMY) {
    carrying = 0;
    max_force = 0.2;
    max_speed = 0.05;
    _attack_damage = 12.5f * UpgradeManager::get_instance()->extra_damage;
    _max_health = 250 * UpgradeManager::get_instance()->extra_hp;
    _health = 250 * UpgradeManager::get_instance()->extra_hp;
    texture = "juggernaut.png";
}

void JuggernautEntity::select() {
    sdl_image_data *entity_data = new sdl_image_data{"sel_" + texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


void JuggernautEntity::deselect() {
    sdl_image_data *entity_data = new sdl_image_data{texture};
    _representation->set_data(entity_data);
    _representation->clear_data();
}


std::string JuggernautEntity::get_texture() {
    return texture;
}

void JuggernautEntity::set_texture(std::string src) {
    this->texture = src;
}
