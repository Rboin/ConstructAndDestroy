//
// Created by Sander on 5-4-2017.
//

#include "fuzzy_set_left_shoulder.h"

double FuzzySetLeftShoulder::calculate_dom(double val)const
{
    //test for the case where the left or right offsets are zero
    //(to prevent divide by zero errors below)
    if ((_right_offset == 0.0 && _peak_point == val) ||
        (_left_off_set == 0.0 && _peak_point == val))
    {
        return 1.0;
    }

        //find DOM if right of center
    else if ( (val >= _peak_point) && (val < (_peak_point + _right_offset)) )
    {
        double grad = 1.0 / -_right_offset;

        return grad * (val - _peak_point) + 1.0;
    }

        //find DOM if left of center
    else if ( (val < _peak_point) && (val >= _peak_point-_left_off_set) )
    {
        return 1.0;
    }

        //out of range of this FLV, return zero
    else
    {
        return 0.0;
    }

}