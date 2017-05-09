//
// Created by Sander on 5-4-2017.
//

#ifndef C_AND_D_PROJECT_FUZZY_VARIABLE_H
#define C_AND_D_PROJECT_FUZZY_VARIABLE_H


#include <map>
#include <iosfwd>
#include <string>

class FuzzySet;
class FzSet;
class FuzzyModule;


class FuzzyVariable
{
private:

    typedef std::map<std::string, FuzzySet*>  member_sets;

private:

    //disallow copies
    FuzzyVariable(const FuzzyVariable&);
    FuzzyVariable& operator=(const FuzzyVariable&);

private:

    //a map of the fuzzy sets that comprise this variable
    member_sets   _member_sets;

    //the minimum and maximum value of the range of this variable
    double        _min_range;
    double        _max_range;


    //this method is called with the upper and lower bound of a set each time a
    //new set is added to adjust the upper and lower range values accordingly
    void adjust_range_to_fit(double min, double max);

    //a client retrieves a reference to a fuzzy variable when an _instance is
    //created via FuzzyModule::create_flv(). To prevent the client from deleting
    //the _instance the FuzzyVariable destructor is made private and the
    //FuzzyModule class made a friend.
    ~FuzzyVariable();

    friend class FuzzyModule;


public:

    FuzzyVariable():_min_range(0.0),_max_range(0.0){}

    //the following methods create instances of the sets named in the method
    //name and add them to the member set map. Each time a set of any type is
    //added the _min_range and _max_range are adjusted accordingly. All of the
    //methods return a proxy class representing the newly created _instance. This
    //proxy set can be used as an operand when creating the rule base.
    FzSet add_left_shoulder_set(std::string name, double minBound, double peak, double maxBound);

    FzSet  add_right_shoulder_set(std::string name, double minBound, double peak, double maxBound);

    FzSet  add_triangular_set(std::string name,
                            double       minBound,
                            double       peak,
                            double       maxBound);

    FzSet  AddSingletonSet(std::string name,
                           double       minBound,
                           double       peak,
                           double       maxBound);


    //fuzzify a value by calculating its DOM in each of this variable's subsets
    void        fuzzify(double val);

    //defuzzify the variable using the max average method
    double       defuzzify_max_av()const;

    //defuzzify the variable using the centroid method
    double       defuzzify_centroid(int num_samples)const;



    std::ostream& write_doms(std::ostream& os);
};


#endif //C_AND_D_PROJECT_FUZZY_VARIABLE_H
