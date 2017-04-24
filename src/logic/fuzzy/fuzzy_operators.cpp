//
// Created by Sander on 5-4-2017.
//

#include <cfloat>
#include "fuzzy_operators.h"
#include "fuzzy_term.h"

///////////////////////////////////////////////////////////////////////////////
//
//  implementation of FzAND
//
///////////////////////////////////////////////////////////////////////////////
FzAND::FzAND(const FzAND& fa)
{
    std::vector<FuzzyTerm*>::const_iterator cur_term;
    for (cur_term = fa._terms.begin(); cur_term != fa._terms.end(); ++cur_term)
    {
        _terms.push_back((*cur_term)->clone());
    }
}

//ctor using two terms
FzAND::FzAND(FuzzyTerm& op1, FuzzyTerm& op2)
{
    _terms.push_back(op1.clone());
    _terms.push_back(op2.clone());
}

//ctor using three terms
FzAND::FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3)
{
    _terms.push_back(op1.clone());
    _terms.push_back(op2.clone());
    _terms.push_back(op3.clone());
}

//ctor using four terms
FzAND::FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4)
{
    _terms.push_back(op1.clone());
    _terms.push_back(op2.clone());
    _terms.push_back(op3.clone());
    _terms.push_back(op4.clone());
}


FzAND::~FzAND()
{
    std::vector<FuzzyTerm*>::iterator cur_term;
    for (cur_term = _terms.begin(); cur_term != _terms.end(); ++cur_term)
    {
        delete *cur_term;
    }
}


//--------------------------- get_dom ------------------------------------------
//
//  the AND operator returns the minimum DOM of the sets it is operating on
//-----------------------------------------------------------------------------
double FzAND::get_dom()const
{
    double smallest = DBL_MAX;

    std::vector<FuzzyTerm*>::const_iterator cur_term;
    for (cur_term = _terms.begin(); cur_term != _terms.end(); ++cur_term)
    {
        if ((*cur_term)->get_dom() < smallest)
        {
            smallest = (*cur_term)->get_dom();
        }
    }

    return smallest;
}


//------------------------- or_with_dom -----------------------------------------
void FzAND::or_with_dom(double val)
{
    std::vector<FuzzyTerm*>::iterator cur_term;
    for (cur_term = _terms.begin(); cur_term != _terms.end(); ++cur_term)
    {
        (*cur_term)->or_with_dom(val);
    }
}

//---------------------------- clear_dom ---------------------------------------
void FzAND::clear_dom()
{
    std::vector<FuzzyTerm*>::iterator cur_term;
    for (cur_term = _terms.begin(); cur_term != _terms.end(); ++cur_term)
    {
        (*cur_term)->clear_dom();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  implementation of FzOR
//
///////////////////////////////////////////////////////////////////////////////
FzOR::FzOR(const FzOR& fa)
{
    std::vector<FuzzyTerm*>::const_iterator cur_term;
    for (cur_term = fa._terms.begin(); cur_term != fa._terms.end(); ++cur_term)
    {
        _terms.push_back((*cur_term)->clone());
    }
}

//ctor using two terms
FzOR::FzOR(FuzzyTerm& op1, FuzzyTerm& op2)
{
    _terms.push_back(op1.clone());
    _terms.push_back(op2.clone());
}

//ctor using three terms
FzOR::FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3)
{
    _terms.push_back(op1.clone());
    _terms.push_back(op2.clone());
    _terms.push_back(op3.clone());
}

//ctor using four terms
FzOR::FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4)
{
    _terms.push_back(op1.clone());
    _terms.push_back(op2.clone());
    _terms.push_back(op3.clone());
    _terms.push_back(op4.clone());
}


FzOR::~FzOR()
{
    std::vector<FuzzyTerm*>::iterator cur_term;
    for (cur_term = _terms.begin(); cur_term != _terms.end(); ++cur_term)
    {
        delete *cur_term;
    }
}


//--------------------------- get_dom ------------------------------------------
//
//  the OR operator returns the maximum DOM of the sets it is operating on
//-----------------------------------------------------------------------------
double FzOR::get_dom()const
{
    double largest = DBL_MIN;

    std::vector<FuzzyTerm*>::const_iterator cur_term;
    for (cur_term = _terms.begin(); cur_term != _terms.end(); ++cur_term)
    {
        if ((*cur_term)->get_dom() > largest)
        {
            largest = (*cur_term)->get_dom();
        }
    }

    return largest;
}
