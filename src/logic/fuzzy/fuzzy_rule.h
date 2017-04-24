//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_RULE_H
#define C_AND_D_PROJECT_FUZZY_RULE_H


#include <vector>
#include "fuzzy_term.h"
#include "fuzzy_set.h"
#include "fuzzy_operators.h"


class FuzzyRule
{
private:

    //antecedent (usually a composite of several fuzzy sets and operators)
    const FuzzyTerm*  _antecedent;

    //consequence (usually a single fuzzy set, but can be several ANDed together)
    FuzzyTerm*        _consequence;

    //it doesn't make sense to allow clients to copy rules
    FuzzyRule(const FuzzyRule&);
    FuzzyRule& operator=(const FuzzyRule&);


public:

    FuzzyRule(const FuzzyTerm& ant,
              const FuzzyTerm& con):_antecedent(ant.clone()),
                                    _consequence(con.clone())
    {}

    ~FuzzyRule(){delete _antecedent; delete _consequence;}

    void set_confidence_of_consequent_to_zero(){_consequence->clear_dom();}

    //this method updates the DOM (the confidence) of the consequent term with
    //the DOM of the antecedent term.
    void calculate()
    {
        _consequence->or_with_dom(_antecedent->get_dom());
    }
};


#endif //C_AND_D_PROJECT_FUZZY_RULE_H
