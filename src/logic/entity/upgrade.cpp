//
// Created by Sander on 7-6-2017.
//

#include "settings.h"
#include "resources.h"
#include "player_manager.h"
#include "player.h"
#include "upgrade.h"
#include "upgrade_manager.h"
#include "moving/moving_entity.h"

Upgrade::Upgrade(Resources *cost, std::string description, std::string name, UpgradeType u_t) {
    _cost = cost;
    _description = description;
    _name = name;
    _upgrade_type = u_t;
    _researched = false;
}

Upgrade::~Upgrade() {
    delete _cost;
}

Resources *Upgrade::get_cost() {
    return _cost;
}

std::string Upgrade::get_name() {
    return _name;
}

std::string Upgrade::get_description() {
    return _description;
}

void Upgrade::upgrade() {
    PlayerManager *pm = PlayerManager::get_instance();
    if (pm->get_player(player_id)->resources->check_if_sufficient_resources(_cost)) {
        switch (_upgrade_type) {
            case UpgradeType::Carry:
                UpgradeManager::get_instance()->carry_rank = 2.0;
                break;
            case UpgradeType::GatherSpeed:
                UpgradeManager::get_instance()->gather_speed = 2.0;
                break;
            case UpgradeType::Health:
                UpgradeManager::get_instance()->extra_hp = 1.15;
                for (int i = 0; i < PlayerManager::get_instance()->get_player(player_id)->units.size(); i++) {
                    PlayerManager::get_instance()->get_player(player_id)->units.at(i)->upgrade_health();
                }
                break;
            case UpgradeType::Attack:
                UpgradeManager::get_instance()->extra_damage = 1.15;
                for (int i = 0; i < PlayerManager::get_instance()->get_player(player_id)->units.size(); i++) {
                    PlayerManager::get_instance()->get_player(player_id)->units.at(i)->upgrade_attack();
                }
                break;
        }
        _researched = true;
        pm->get_player(player_id)->resources->subtract_resources(_cost);


    }

}

UpgradeType Upgrade::get_upgrade_type() {
    return _upgrade_type;
}

bool Upgrade::is_researched() {
    return _researched;
}


