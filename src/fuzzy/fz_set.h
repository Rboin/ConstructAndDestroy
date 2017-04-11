//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FZ_SET_H
#define C_AND_D_PROJECT_FZ_SET_H


#include "fuzzy_term.h"
#include "fuzzy_set.h"


class FzSet : public FuzzyTerm
{
private:

    //let the hedge classes be friends
    friend class FzVery;
    friend class FzFairly;

private:

    //a reference to the fuzzy set this proxy represents
    FuzzySet& _set;

public:

    FzSet(FuzzySet& fs):_set(fs){}

    FuzzyTerm* clone()const{return new FzSet(*this);}
    double     get_dom()const {return _set.get_dom();}
    void       clear_dom(){_set.clear_dom();}
    void       or_with_dom(double val){_set.or_with_dom(val);}
};


#endif //C_AND_D_PROJECT_FZ_SET_H
