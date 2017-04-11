//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_TERM_H
#define C_AND_D_PROJECT_FUZZY_TERM_H


class FuzzyTerm
{
public:

    virtual ~FuzzyTerm(){}

    //all terms must implement a virtual constructor
    virtual FuzzyTerm* clone()const = 0;

    //retrieves the degree of membership of the term
    virtual double      get_dom()const=0;

    //clears the degree of membership of the term
    virtual void       clear_dom()=0;

    //method for updating the DOM of a consequent when a rule fires
    virtual void       or_with_dom(double val)=0;


};


#endif //C_AND_D_PROJECT_FUZZY_TERM_H
