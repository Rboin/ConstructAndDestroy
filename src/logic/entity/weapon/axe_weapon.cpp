//
// Created by Sander on 6-4-2017.
//

#include "axe_weapon.h"

Axe::Axe() {
    initialize_fuzzy_module();
}

double Axe::get_desirability(double distance_to_target) {
    //fuzzify distance and amount of ammo
    _fuzzyModule.fuzzify("distance_to_target", distance_to_target);

    _desirability = _fuzzyModule.defuzzify("desirability", FuzzyModule::max_av);

    return _desirability;
}

void Axe::initialize_fuzzy_module() {
    FuzzyVariable &distance_to_target = _fuzzyModule.create_flv("distance_to_target");
    FzSet target_close = distance_to_target.add_left_shoulder_set("target_close", 0, 25, 150);
    FzSet target_medium = distance_to_target.add_triangular_set("target_medium", 25, 150, 300);
    FzSet target_far = distance_to_target.add_right_shoulder_set("target_far", 150, 300, 1000);

    FuzzyVariable &desirability = _fuzzyModule.create_flv("desirability");
    FzSet very_desirable = desirability.add_right_shoulder_set("very_desirable", 50, 75, 100);
    FzSet desirable = desirability.add_triangular_set("desirable", 25, 50, 75);
    FzSet undesirable = desirability.add_left_shoulder_set("undesirable", 0, 25, 50);

    _fuzzyModule.add_rule(target_close, very_desirable);
    _fuzzyModule.add_rule(target_medium, desirable);
    _fuzzyModule.add_rule(target_far, undesirable);
}

TextureTypes Axe::get_texture() {
    return _texture;
}
