//
// Created by Sander on 7-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_UPGRADE_MANAGER_H
#define CONSTRUCT_AND_DESTROY_UPGRADE_MANAGER_H


#include <vector>
#include "upgrade_type.h"
#include <string>

struct upgrade_with_texture{
    std::string texture;
    UpgradeType type;
};

class Upgrade;

class UpgradeManager {
private:
    UpgradeManager();
    static UpgradeManager *_instance;
public:
    ~UpgradeManager();

    void setup();

    static UpgradeManager *get_instance();

    void reset();

    std::vector<Upgrade*> upgrades;
    std::vector<upgrade_with_texture> upgrade_with_textures;
    std::string get_texture_of_upgrade(UpgradeType type);

    //================ Upgrades ================
    float carry_rank;
    float gather_speed;
    float extra_hp;
    float extra_damage;
//===============================================
};


#endif //CONSTRUCT_AND_DESTROY_UPGRADE_MANAGER_H
