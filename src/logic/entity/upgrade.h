//
// Created by Sander on 7-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_UPGRADE_H
#define CONSTRUCT_AND_DESTROY_UPGRADE_H

#include <string>
#include "upgrade_type.h"

class Resources;


class Upgrade {
private:
    Resources *_cost;
    std::string _description;
    std::string _name;
    UpgradeType _upgrade_type;
    bool _researched;
public:
    Upgrade(Resources *cost, std::string description, std::string name, UpgradeType e_t);

    ~Upgrade();

    Resources *get_cost();

    std::string get_name();

    std::string get_description();

    UpgradeType get_upgrade_type();

    bool is_researched();

    void upgrade();
};


#endif //CONSTRUCT_AND_DESTROY_UPGRADE_H
