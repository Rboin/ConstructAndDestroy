//
// Created by Sander on 5-4-2017.
//

#include <iostream>
#include "fuzzy_module.h"

//------------------------------ dtor -----------------------------------------
FuzzyModule::~FuzzyModule()
{
    var_map::iterator cur_var = _variables.begin();
    for (cur_var; cur_var != _variables.end(); ++cur_var)
    {
        delete cur_var->second;
    }

    std::vector<FuzzyRule*>::iterator cur_rule = _rules.begin();
    for (cur_rule; cur_rule != _rules.end(); ++cur_rule)
    {
        delete *cur_rule;
    }
}

//----------------------------- add_rule ---------------------------------------
void FuzzyModule::add_rule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
    _rules.push_back(new FuzzyRule(antecedent, consequence));
}


//-------------------------- create_flv ---------------------------
//
//  creates a new fuzzy variable and returns a reference to it
//-----------------------------------------------------------------------------
FuzzyVariable& FuzzyModule::create_flv(const std::string& name)
{
    _variables[name] = new FuzzyVariable();;

    return *_variables[name];
}


//---------------------------- write_all_doms -----------------------------------
std::ostream& FuzzyModule::write_all_doms(std::ostream& os)
{
    os << "\n\n";

    var_map::iterator cur_var = _variables.begin();
    for (cur_var; cur_var != _variables.end(); ++cur_var)
    {
        os << "\n--------------------------- " << cur_var->first;;
        cur_var->second->write_doms(os);

        os << std::endl;
    }

    return os;
}

