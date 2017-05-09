//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_OPERATERS_H
#define C_AND_D_PROJECT_FUZZY_OPERATERS_H

#include <vector>
#include <cassert>
#include "fuzzy_term.h"

///////////////////////////////////////////////////////////////////////////////
//
//  a fuzzy AND operator class
//
///////////////////////////////////////////////////////////////////////////////
class FzAND : public FuzzyTerm
{
private:

    //an instance of this class may AND together up to 4 terms
    std::vector<FuzzyTerm*> _terms;

    //disallow assignment
    FzAND& operator=(const FzAND&);

public:

    ~FzAND();

    //copy ctor
    FzAND(const FzAND& fa);

    //ctors accepting fuzzy terms.
    FzAND(FuzzyTerm& op1, FuzzyTerm& o2);
    FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3);
    FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4);

    //virtual ctor
    FuzzyTerm* clone()const{return new FzAND(*this);}

    double get_dom()const;
    void  clear_dom();
    void  or_with_dom(double val);
};


///////////////////////////////////////////////////////////////////////////////
//
//  a fuzzy OR operator class
//
///////////////////////////////////////////////////////////////////////////////
class FzOR : public FuzzyTerm
{
private:

    //an instance of this class may AND together up to 4 terms
    std::vector<FuzzyTerm*> _terms;

    //no assignment op necessary
    FzOR& operator=(const FzOR&);

public:

    ~FzOR();

    //copy ctor
    FzOR(const FzOR& fa);

    //ctors accepting fuzzy terms.
    FzOR(FuzzyTerm& op1, FuzzyTerm& op2);
    FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3);
    FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4);

    //virtual ctor
    FuzzyTerm* clone()const{return new FzOR(*this);}

    double get_dom()const;

    //unused
    void clear_dom(){assert(0 && "<FzOR::clear_dom>: invalid context");}
    void or_with_dom(double val){assert(0 && "<FzOR::or_with_dom>: invalid context");}
};


#endif //C_AND_D_PROJECT_FUZZY_OPERATERS_H
