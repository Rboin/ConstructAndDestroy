//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_GOAL_COMPOSITE_H
#define C_AND_D_PROJECT_GOAL_COMPOSITE_H

#include <deque>
#include <algorithm>
#include "goal.h"
#include "entity/goal/moving_entity_goal/level_type.h"

template<typename T>
class GoalComposite : public Goal<T> {
protected:
    std::deque<Goal<T> *> sub_goals;
public:
    GoalComposite(T *t, int gt) : Goal<T>(t, gt, STRATEGY) {
        sub_goals = std::deque<Goal<T> *>();
    };

    GoalComposite(T *t, int gt, int initiator) : Goal<T>(t, gt, STRATEGY, initiator) {
        sub_goals = std::deque<Goal<T> *>();
    };

    virtual ~GoalComposite() {
        remove_all_subgoals();
    };

    std::deque<Goal<T> *> get_sub_goals() {
        return sub_goals;
    }

    Goal<T>* get_active_goal() {
        if (!sub_goals.empty())
            return sub_goals.front();

        return nullptr;
    }

    void add_subgoal(Goal<T> *goal, bool front) {
        bool found = false;
        for(typename std::deque<Goal<T> *>::iterator it = sub_goals.begin(); it != sub_goals.end(); it++) {
            Goal<T> * current_goal = (*it);
            if(goal->get_type() == current_goal->get_type()) {
                found = true;
                break;
            }
        }
        if(!found)
            front ? sub_goals.push_front(goal) : sub_goals.push_back(goal);
    }

    void add_priority_subgoal(Goal<T> *goal) {
        add_subgoal(goal, true);
    };

    void add_subgoal(Goal<T> *goal) {
        add_subgoal(goal, false);
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

            if (current->is_active()) {
                current->terminate();
            }

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
