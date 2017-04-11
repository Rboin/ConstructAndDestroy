//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_HEDGES_H
#define C_AND_D_PROJECT_FUZZY_HEDGES_H


#include "fuzzy_set.h"
#include "fuzzy_term.h"
#include "fz_set.h"
#include <math.h>

class FzVery : public FuzzyTerm
{
private:

    FuzzySet& _set;

    //prevent copying and assignment by clients
    FzVery(const FzVery& inst):_set(inst._set){}
    FzVery& operator=(const FzVery&);


public:

    FzVery(FzSet& ft):_set(ft._set){}

    double get_dom()const
    {
        return _set.get_dom() * _set.get_dom();
    }

    FuzzyTerm* clone()const{return new FzVery(*this);}

    void clear_dom(){_set.clear_dom();}
    void or_with_dom(double val){_set.or_with_dom(val * val);}
};

///////////////////////////////////////////////////////////////////////////////
class FzFairly : public FuzzyTerm
{
private:

    FuzzySet& _set;

    //prevent copying and assignment
    FzFairly(const FzFairly& inst):_set(inst._set){}
    FzFairly& operator=(const FzFairly&);

public:

    FzFairly(FzSet& ft):_set(ft._set){}

    double get_dom()const
    {
        return sqrt(_set.get_dom());
    }

    FuzzyTerm* clone()const{return new FzFairly(*this);}

    void clear_dom(){_set.clear_dom();}
    void or_with_dom(double val){_set.or_with_dom(sqrt(val));}
};


#endif //C_AND_D_PROJECT_FUZZY_HEDGES_H
