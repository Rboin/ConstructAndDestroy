//
// Created by Sander on 5-4-2017.
//

#include "fuzzy_set_right_shoulder.h"

double FuzzySetRightShoulder::calculate_dom(double val) const {
    //test for the case where the left or right offsets are zero
    //(to prevent divide by zero errors below)
    if ((_right_offset == 0.0 && _peak_point == val) ||
        (_left_off_set == 0.0 && _peak_point == val)) {
        return 1.0;
    }

        //find DOM if left of center
    else if ((val <= _peak_point) && (val > (_peak_point - _left_off_set))) {
        double grad = 1.0 / _left_off_set;

        return grad * (val - (_peak_point - _left_off_set));
    }
        //find DOM if right of center and less than center + right offset
    else if ((val > _peak_point) && (val <= _peak_point + _right_offset)) {
        return 1.0;
    } else {
        return 0;
    }
}