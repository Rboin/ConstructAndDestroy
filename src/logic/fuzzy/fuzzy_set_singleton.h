//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_SET_SINGLETON_H
#define C_AND_D_PROJECT_FUZZY_SET_SINGLETON_H


#include "fuzzy_set.h"

class FuzzySetSingleton : public FuzzySet {
private:

    //the values that define the shape of this FLV
    double _mid_point;
    double _left_off_set;
    double _right_offset;

public:

    FuzzySetSingleton(double mid,
                      double lft,
                      double rgt) : FuzzySet(mid),
                                    _mid_point(mid),
                                    _left_off_set(lft),
                                    _right_offset(rgt) {}

    //this method calculates the degree of membership for a particular value
    double calculate_dom(double val) const;
};


#endif //C_AND_D_PROJECT_FUZZY_SET_SINGLETON_H
