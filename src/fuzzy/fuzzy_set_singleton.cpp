//
// Created by Sander on 5-4-2017.
//

#include "fuzzy_set_singleton.h"

double FuzzySetSingleton::calculate_dom(double val)const
{
    if ( (val >= _mid_point-_left_off_set) &&
         (val <= _mid_point+_right_offset) )
    {
        return 1.0;
    }

        //out of range of this FLV, return zero
    else
    {
        return 0.0;
    }
}
