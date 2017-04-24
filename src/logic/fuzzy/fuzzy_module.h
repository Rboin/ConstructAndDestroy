//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_MODULE_H
#define C_AND_D_PROJECT_FUZZY_MODULE_H


#include <vector>
#include <string>
#include <map>
#include <iosfwd>
#include <assert.h>
#include "fuzzy_variable.h"
#include "fuzzy_rule.h"
#include "fuzzy_term.h"
#include "fuzzy_set.h"
#include "fuzzy_operators.h"
#include "fz_set.h"
#include "fuzzy_hedges.h"

class FuzzyModule
{
private:

    typedef std::map<std::string, FuzzyVariable*> var_map;

public:

    //you must pass one of these values to the defuzzify method. This module
    //only supports the MaxAv and centroid methods.
    enum defuzzify_method{max_av, centroid};

    //when calculating the centroid of the fuzzy manifold this value is used
    //to determine how many cross-sections should be sampled
    enum {num_samples = 15};

private:

    //a map of all the fuzzy variables this module uses
    var_map                   _variables;

    //a vector containing all the fuzzy rules
    std::vector<FuzzyRule*>   _rules;


    //zeros the DOMs of the consequents of each rule. Used by defuzzify()
    inline void set_confidences_of_consequents_to_zero();


public:

    ~FuzzyModule();

    //creates a new 'empty' fuzzy variable and returns a reference to it.
    FuzzyVariable&  create_flv(const std::string& name);

    //adds a rule to the module
    void            add_rule(FuzzyTerm& antecedent, FuzzyTerm& consequence);

    //this method calls the fuzzify method of the named FLV
    inline void     fuzzify(const std::string& name_of_flv, double val);

    //given a fuzzy variable and a deffuzification method this returns a
    //crisp value
    inline double    defuzzify(const std::string& key,
                               defuzzify_method    method = max_av);


    //writes the DOMs of all the variables in the module to an output stream
    std::ostream&   write_all_doms(std::ostream& os);

};

///////////////////////////////////////////////////////////////////////////////

//----------------------------- fuzzify ---------------------------------------
//
//  this method calls the fuzzify method of the variable with the same name
//  as the key
//-----------------------------------------------------------------------------
inline void FuzzyModule::fuzzify(const std::string& name_of_flv, double val)
{
    //first make sure the key exists
    assert ( (_variables.find(name_of_flv) != _variables.end()) &&
             "<FuzzyModule::fuzzify>:key not found");

    _variables[name_of_flv]->fuzzify(val);
}

//---------------------------- defuzzify --------------------------------------
//
//  given a fuzzy variable and a deffuzification method this returns a
//  crisp value
//-----------------------------------------------------------------------------
inline double
FuzzyModule::defuzzify(const std::string& name_of_flv, defuzzify_method method)
{
    //first make sure the key exists
    assert ( (_variables.find(name_of_flv) != _variables.end()) &&
             "<FuzzyModule::defuzzify_max_av>:key not found");

    //clear the DOMs of all the consequents of all the rules
    set_confidences_of_consequents_to_zero();

    //process the rules
    std::vector<FuzzyRule*>::iterator cur_rule = _rules.begin();
    for (cur_rule; cur_rule != _rules.end(); ++cur_rule)
    {
        (*cur_rule)->calculate();
    }

    //now defuzzify the resultant conclusion using the specified method
    switch (method)
    {
        case centroid:

            return _variables[name_of_flv]->defuzzify_centroid(num_samples);

            break;

        case max_av:

            return _variables[name_of_flv]->defuzzify_max_av();

            break;
    }

    return 0;
}



//-------------------------- ClearConsequents ---------------------------------
//
//  zeros the DOMs of the consequents of each rule
//-----------------------------------------------------------------------------
inline void FuzzyModule::set_confidences_of_consequents_to_zero()
{
    std::vector<FuzzyRule*>::iterator cur_rule = _rules.begin();
    for (cur_rule; cur_rule != _rules.end(); ++cur_rule)
    {
        (*cur_rule)->set_confidence_of_consequent_to_zero();
    }
}



#endif //C_AND_D_PROJECT_FUZZY_MODULE_H
