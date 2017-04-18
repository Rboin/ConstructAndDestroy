//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_GOAL_H
#define C_AND_D_PROJECT_GOAL_H

enum ProcessStatus {
    INACTIVE, ACTIVE, COMPLETED, FAILED
};

template<typename T>
class Goal {
protected:
    T *owner;
    int status;
    int type;
    int level_type;
public:
    Goal(T *t, int gt, int lt) {
        owner = t;
        type = gt;
        status = INACTIVE;
        level_type = lt;
    };

    const bool is_active() {
        return status == ACTIVE;
    };

    const bool is_inactive() {
        return status == INACTIVE;
    };

    const bool is_completed() {
        return status == COMPLETED;
    };

    const bool has_failed() {
        return status == FAILED;
    };

    const int get_type() {
        return type;
    };

    const int get_level_type() const {
        return level_type;
    }

    virtual void activate_if_inactive() {
        if(is_inactive())
            activate();
    };

    virtual ~Goal() {
        owner = nullptr;
    };

    /**
     * Method contains the initialization logic and planning phase for the goal.
     */
    virtual void activate() = 0;

    /**
     * Processes the goal and returns an enumerated value of the ProcessStatus enum.
     * @return ProcessStatus
     */
    virtual const int process() = 0;

    /**
     * Clears and destroys the goal.
     */
    virtual void terminate() = 0;

    /**
     * Adds subgoals for composite goal.
     */
    virtual void add_subgoal(Goal<T> *) = 0;

    virtual const char *get_name() const = 0;
};

#endif //C_AND_D_PROJECT_GOAL_H
