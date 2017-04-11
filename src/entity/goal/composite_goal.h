//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_GOAL_COMPOSITE_H
#define C_AND_D_PROJECT_GOAL_COMPOSITE_H

#include <deque>
#include <algorithm>
#include "goal.h"
#include "moving_entity_goal/level_type.h"

template<typename T>
class GoalComposite : public Goal<T> {
protected:
    std::deque<Goal<T> *> sub_goals;
public:
    GoalComposite(T *t, int gt) : Goal<T>(t, gt, STRATEGY) {
        sub_goals = std::deque<Goal<T> *>();
    };

    virtual ~GoalComposite() {
        remove_all_subgoals();
    };

    std::deque<Goal<T> *> get_sub_goals() {
        return sub_goals;
    }

    void add_subgoal(Goal<T> *goal) {
        bool found = false;
        for(typename std::deque<Goal<T> *>::iterator it = sub_goals.begin(); it != sub_goals.end(); it++) {
            Goal<T> * current_goal = (*it);
            if(goal->get_type() == current_goal->get_type()) {
                found = true;
                break;
            }
        }
        if(!found)
            sub_goals.push_back(goal);
    };

    int process_subgoals() {
        Goal<T> *top;
        while (!sub_goals.empty() && ((top = sub_goals.back())->is_completed() || top->has_failed())) {
            top->terminate();
            sub_goals.pop_back();
            delete top;
        }
        if (!sub_goals.empty()) {
            top = sub_goals.back();
            int sub_goals_status = top->process();
            if (sub_goals_status == COMPLETED || sub_goals.size() > 1)
                return ACTIVE;
            return sub_goals_status;
        } else
            return COMPLETED;
    };

    void remove_all_subgoals() {
        while (!sub_goals.empty()) {
            Goal<T> *current = sub_goals.back();
            sub_goals.pop_back();

            current->terminate();
            delete current;
        }
    };

    virtual const int process() {
        this->activate_if_inactive();
        return process_subgoals();
    };

    virtual void activate() = 0;

    virtual void terminate() = 0;
};

#endif //C_AND_D_PROJECT_GOAL_COMPOSITE_H
