//
// Created by Sander on 6-4-2017.
//

#ifndef C_AND_D_PROJECT_BOW_WEAPON_H
#define C_AND_D_PROJECT_BOW_WEAPON_H

#include "textures/texture_types.h"
#include "weapon.h"

class MovingEntity;

class Bow : public Weapon {
private:
    FuzzyModule _fuzzyModule;

    void initialize_fuzzy_module();

    const TextureTypes _texture = BOWTEXTURE;

public:
    Bow();

    double get_desirability(double);

    TextureTypes get_texture();
};


#endif //C_AND_D_PROJECT_BOW_WEAPON_H
