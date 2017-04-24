//
// Created by Sander on 5-4-2017.
//

#include "fuzzy_variable.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include "fuzzy/fuzzy_set_singleton.h"
#include "fuzzy/fuzzy_set_right_shoulder.h"
#include "fuzzy/fuzzy_set_left_shoulder.h"
#include "fuzzy_operators.h"
#include "fuzzy_set_triangle.h"
#include "fz_set.h"

//------------------------------ dtor -----------------------------------------
//-----------------------------------------------------------------------------
FuzzyVariable::~FuzzyVariable()
{
    member_sets::iterator it;
    for (it = _member_sets.begin(); it != _member_sets.end(); ++it)
    {
        delete it->second;
    }
}

//--------------------------- fuzzify -----------------------------------------
//
//  takes a crisp value and calculates its degree of membership for each set
//  in the variable.
//-----------------------------------------------------------------------------
void FuzzyVariable::fuzzify(double val)
{
    //make sure the value is within the bounds of this variable
//    assert ( (val >= _min_range) && (val <= _max_range) &&
//             "<FuzzyVariable::fuzzify>: value out of range");

    //for each set in the flv calculate the DOM for the given value
    member_sets::const_iterator cur_set;
    for (cur_set = _member_sets.begin(); cur_set != _member_sets.end(); ++cur_set)
    {
        cur_set->second->set_dom(cur_set->second->calculate_dom(val));
    }
}


//--------------------------- defuzzify_max_av ----------------------------------
//
// defuzzifies the value by averaging the maxima of the sets that have fired
//
// OUTPUT = sum (maxima * DOM) / sum (DOMs)
//-----------------------------------------------------------------------------
double FuzzyVariable::defuzzify_max_av()const
{
    double bottom = 0.0;
    double top    = 0.0;

    member_sets::const_iterator cur_set;
    for (cur_set = _member_sets.begin(); cur_set != _member_sets.end(); ++cur_set)
    {
        bottom += cur_set->second->get_dom();

        top += cur_set->second->get_representative_val() * cur_set->second->get_dom();
    }

    //make sure bottom is not equal to zero
    if (0 == bottom) return 0.0;

    return top / bottom;
}

//------------------------- defuzzify_centroid ---------------------------------
//
//  defuzzify the variable using the centroid method
//-----------------------------------------------------------------------------
double FuzzyVariable::defuzzify_centroid(int num_samples)const
{
    //calculate the step size
    double step_size = (_max_range - _min_range)/(double)num_samples;

    double total_area    = 0.0;
    double sum_of_moments = 0.0;

    //step through the range of this variable in increments equal to step_size
    //adding up the contribution (lower of calculate_dom or the actual DOM of this
    //variable's fuzzified value) for each subset. This gives an approximation of
    //the total area of the fuzzy manifold.(This is similar to how the area under
    //a curve is calculated using calculus... the heights of lots of 'slices' are
    //summed to give the total area.)
    //
    //in addition the moment of each slice is calculated and summed. Dividing
    //the total area by the sum of the moments gives the centroid. (Just like
    //calculating the center of mass of an object)
    for (int samp=1; samp<=num_samples; ++samp)
    {
        //for each set get the contribution to the area. This is the lower of the
        //value returned from calculate_dom or the actual DOM of the fuzzified
        //value itself
        member_sets::const_iterator cur_set = _member_sets.begin();
        for (cur_set; cur_set != _member_sets.end(); ++cur_set)
        {
            double contribution =
                    std::min(cur_set->second->calculate_dom(_min_range + samp * step_size),
                          cur_set->second->get_dom());

            total_area += contribution;

            sum_of_moments += (_min_range + samp * step_size)  * contribution;
        }
    }

    //make sure total area is not equal to zero
    if (0 == total_area) return 0.0;

    return (sum_of_moments / total_area);
}

//------------------------- add_triangular_set ----------------------------------
//
//  adds a triangular shaped fuzzy set to the variable
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::add_triangular_set(std::string name,
                                      double       min_bound,
                                      double       peak,
                                      double       max_bound)
{
    _member_sets[name] = new FuzzySetTriangle(peak,
                                               peak-min_bound,
                                               max_bound-peak);
    //adjust range if necessary
    adjust_range_to_fit(min_bound, max_bound);

    return FzSet(*_member_sets[name]);
}

//--------------------------- AddLeftShoulder ---------------------------------
//
//  adds a left shoulder type set
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::add_left_shoulder_set(std::string name,
                                          double       min_bound,
                                          double       peak,
                                          double       max_bound)
{
    _member_sets[name] = new FuzzySetLeftShoulder(peak, peak-min_bound, max_bound-peak);

    //adjust range if necessary
    adjust_range_to_fit(min_bound, max_bound);
    return FzSet(*_member_sets[name]);
}


//--------------------------- AddRightShoulder ---------------------------------
//
//  adds a left shoulder type set
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::add_right_shoulder_set(std::string name,
                                         double       min_bound,
                                         double       peak,
                                         double       max_bound)
{
    _member_sets[name] = new FuzzySetRightShoulder(peak, peak-min_bound, max_bound-peak);

    //adjust range if necessary
    adjust_range_to_fit(min_bound, max_bound);

    return FzSet(*_member_sets[name]);
}


//--------------------------- AddSingletonSet ---------------------------------
//
//  adds a singleton to the variable
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddSingletonSet(std::string name,
                                     double       min_bound,
                                     double       peak,
                                     double       max_bound)
{
    _member_sets[name] = new FuzzySetSingleton(peak,
                                                peak-min_bound,
                                                max_bound-peak);

    adjust_range_to_fit(min_bound, max_bound);

    return FzSet(*_member_sets[name]);
}

//---------------------------- adjust_range_to_fit -------------------------------
//
//  this method is called with the upper and lower bound of a set each time a
//  new set is added to adjust the upper and lower range values accordingly
//-----------------------------------------------------------------------------
void FuzzyVariable::adjust_range_to_fit(double min_bound, double max_bound)
{
    if (min_bound < _min_range) _min_range = min_bound;
    if (max_bound > _max_range) _max_range = max_bound;
}

//---------------------------- write_doms --------------------------------------
std::ostream& FuzzyVariable::write_doms(std::ostream& os)
{
    member_sets::iterator it;
    for (it = _member_sets.begin(); it != _member_sets.end(); ++it)
    {

        os << "\n" << it->first << " is " << it->second->get_dom();
    }

    os << "\nMin Range: " << _min_range << "\nMax Range: " << _max_range;

    return os;

}