//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_SET_H
#define C_AND_D_PROJECT_FUZZY_SET_H


#include <string>
#include <cassert>


class FuzzySet
{
protected:

    //this will hold the degree of membership of a given value in this set
    double        _dom;

    //this is the maximum of the set's membership function. For instamce, if
    //the set is triangular then this will be the peak point of the triangular.
    //if the set has a plateau then this value will be the mid point of the
    //plateau. This value is set in the constructor to avoid run-time
    //calculation of mid-point values.
    double        _representative_value;

public:

    FuzzySet(double rep_val):_dom(0.0), _representative_value(rep_val){}

    //return the degree of membership in this set of the given value. NOTE,
    //this does not set _dom to the DOM of the value passed as the parameter.
    //This is because the centroid defuzzification method also uses this method
    //to determine the DOMs of the values it uses as its sample points.
    virtual double      calculate_dom(double val)const = 0;

    //if this fuzzy set is part of a consequent FLV, and it is fired by a rule
    //then this method sets the DOM (in this context, the DOM represents a
    //confidence level)to the maximum of the parameter value or the set's
    //existing _dom value
    void               or_with_dom(double val){if (val > _dom) _dom = val;}

    //accessor methods
    double             get_representative_val()const{return _representative_value;}

    void               clear_dom(){_dom = 0.0;}
    double             get_dom()const{return _dom;}
    void               set_dom(double val)
    {
        assert ((val <=1) && (val >= 0) && "<FuzzySet::set_dom>: invalid value");
        _dom = val;
    }
};


#endif //C_AND_D_PROJECT_FUZZY_SET_H
