//
// Created by Sander on 6-4-2017.
//

#ifndef C_AND_D_PROJECT_AXE_WEAPON_H
#define C_AND_D_PROJECT_AXE_WEAPON_H


#include <textures/texture_types.h>
#include "weapon.h"

class MovingEntity;

class Axe : Weapon {
private:
    FuzzyModule _fuzzyModule;
    void     initialize_fuzzy_module();
    double _desirability;
    const TextureTypes _texture = AXETEXTURE;

public:
    Axe();

    double get_desirability(double);

    TextureTypes get_texture();
};


#endif //C_AND_D_PROJECT_AXE_WEAPON_H
