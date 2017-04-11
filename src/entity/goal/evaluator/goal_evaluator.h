//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_GOAL_EVALUATOR_H
#define C_AND_D_PROJECT_GOAL_EVALUATOR_H

template<typename T>
class GoalEvaluator {
public:
    /**
     * calculate desirability for goal.
     * @return float value in range [0,...,1]
     */
    virtual const float calculate_desirability(T *) = 0;

    /**
     * Calls the set method of the think goal.
     */
    virtual void set_goal(T *) = 0;
};

#endif //C_AND_D_PROJECT_GOAL_EVALUATOR_H
