//
// Created by Sander on 6-4-2017.
//

#ifndef C_AND_D_PROJECT_WEAPON_H
#define C_AND_D_PROJECT_WEAPON_H


#include <fuzzy/fuzzy_module.h>
#include "textures/texture_types.h"
class Weapon {
private:
    virtual void     initialize_fuzzy_module() = 0;
protected:
    double _ammo;
    double _desirability;
public:
    virtual double get_desirability(double) = 0;
    virtual TextureTypes get_texture() = 0;
};


#endif //C_AND_D_PROJECT_WEAPON_H
