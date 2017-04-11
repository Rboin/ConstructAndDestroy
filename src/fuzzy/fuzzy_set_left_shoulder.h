//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_SET_LEFT_SHOULDER_H
#define C_AND_D_PROJECT_FUZZY_SET_LEFT_SHOULDER_H


#include "fuzzy_set.h"

class FuzzySetLeftShoulder : public FuzzySet
{
private:

    //the values that define the shape of this FLV
    double   _peak_point;
    double   _right_offset;
    double   _left_off_set;

public:

    FuzzySetLeftShoulder(double peak,
                          double _left_off_set,
                          double _right_off_set):

            FuzzySet( ((peak - _left_off_set) + peak) / 2),
            _peak_point(peak),
            _left_off_set(_left_off_set),
            _right_offset(_right_off_set)
    {}

    //this method calculates the degree of membership for a particular value
    double calculate_dom(double val)const;
};


#endif //C_AND_D_PROJECT_FUZZY_SET_LEFT_SHOULDER_H
