//
// Created by Sander on 7-6-2017.
//

#include "upgrade_manager.h"
#include "resources.h"
#include "upgrade.h"

UpgradeManager *UpgradeManager::_instance = nullptr;

UpgradeManager *UpgradeManager::get_instance() {
    if (!_instance) {
        _instance = new UpgradeManager();
    }
    return _instance;
}

UpgradeManager::UpgradeManager() {
    setup();
}

UpgradeManager::~UpgradeManager() {

}

void UpgradeManager::setup() {
    carry_rank = 1;
    gather_speed = 1;
    extra_hp = 1;
    extra_damage = 1;
    upgrade_with_textures = {
            {"cart.png",   UpgradeType::Carry},
            {"tools.png",  UpgradeType::GatherSpeed},
            {"health.png", UpgradeType::Health},
            {"knife.png",  UpgradeType::Attack}
    };

    upgrades = {
            {new Upgrade(new Resources(100, 0, 0, 0), "Upgrade the carrying capacity of all workers.", "Carry capacity",
                         Carry)},
            {new Upgrade(new Resources(100, 0, 0, 0), "Upgrade the gather speed of all workers.", "Gather Speed",
                         GatherSpeed)},
            {new Upgrade(new Resources(150, 0, 0, 0), "All your units get 15% more HP.", "Health", Health)},
            {new Upgrade(new Resources(250, 0, 0, 0), "All your units do 20% extra damage.", "Damage", Attack)},
    };

}

std::string UpgradeManager::get_texture_of_upgrade(UpgradeType type) {
    for (int i = 0; i < upgrade_with_textures.size(); i++) {
        if (upgrade_with_textures.at(i).type == type) {
            return upgrade_with_textures.at(i).texture;
        }
    }
}

void UpgradeManager::reset() {
    upgrades.clear();
    upgrade_with_textures.clear();
    setup();
}

