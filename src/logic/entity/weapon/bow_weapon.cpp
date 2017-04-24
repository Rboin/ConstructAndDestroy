//
// Created by Sander on 6-4-2017.
//

#include "bow_weapon.h"

Bow::Bow() {
    initialize_fuzzy_module();
    _ammo = 100;
}

double Bow::get_desirability(double distance_to_target) {
    //fuzzify distance and amount of ammo
    if (_ammo == 0) {
        _desirability = 0;
    } else {
        _fuzzyModule.fuzzify("distance_to_target", distance_to_target);
        _fuzzyModule.fuzzify("ammo_status", _ammo);
        _desirability = _fuzzyModule.defuzzify("desirability", FuzzyModule::max_av);
    }
    return _desirability;
}

void Bow::initialize_fuzzy_module() {
    FuzzyVariable &distance_to_target = _fuzzyModule.create_flv("distance_to_target");
    FzSet target_close = distance_to_target.add_left_shoulder_set("target_close", 0, 25, 150);
    FzSet target_medium = distance_to_target.add_triangular_set("target_medium", 25, 150, 300);
    FzSet target_far = distance_to_target.add_right_shoulder_set("target_far", 150, 300, 1000);

    FuzzyVariable &desirability = _fuzzyModule.create_flv("desirability");

    FzSet very_desirable = desirability.add_right_shoulder_set("very_desirable", 50, 75, 100);
    FzSet desirable = desirability.add_triangular_set("desirable", 25, 50, 75);
    FzSet undesirable = desirability.add_left_shoulder_set("undesirable", 0, 25, 50);

    FuzzyVariable &ammo_status = _fuzzyModule.create_flv("ammo_status");
    FzSet ammo_loads = ammo_status.add_right_shoulder_set("ammo_loads", 15, 30, 100);
    FzSet ammo_okay = ammo_status.add_triangular_set("ammo_okay", 0, 15, 30);
    FzSet ammo_low = ammo_status.add_triangular_set("ammo_low", 0, 0, 15);

    FzAND t1 = FzAND(target_close, ammo_loads);
    _fuzzyModule.add_rule(t1, desirable);
    FzAND t2 = FzAND(target_close, ammo_okay);
    _fuzzyModule.add_rule(t2, desirable);
    FzAND t3 = FzAND(target_close, ammo_low);
    _fuzzyModule.add_rule(t3, undesirable);

    FzAND t4 = FzAND(target_medium, ammo_loads);
    _fuzzyModule.add_rule(t4, very_desirable);
    FzAND t5 = FzAND(target_medium, ammo_okay);
    _fuzzyModule.add_rule(t5, desirable);
    FzAND t6 = FzAND(target_medium, ammo_low);
    _fuzzyModule.add_rule(t6, desirable);

    FzAND t7 = FzAND(target_far, ammo_loads);
    _fuzzyModule.add_rule(t7, very_desirable);
    FzAND t8 = FzAND(target_far, ammo_okay);
    _fuzzyModule.add_rule(t8, very_desirable);
    FzAND t9 = FzAND(target_far, ammo_low);
    _fuzzyModule.add_rule(t9, very_desirable);
}

TextureTypes Bow::get_texture() {
    return _texture;
}
