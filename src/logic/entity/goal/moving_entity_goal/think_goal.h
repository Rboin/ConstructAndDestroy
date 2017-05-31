//
// Created by robin on 3/11/17.
//

#ifndef C_AND_D_PROJECT_THINK_GOAL_H
#define C_AND_D_PROJECT_THINK_GOAL_H

#include <vector>
#include "types.h"
#include "goal/composite_goal.h"
#include "job_type.h"
#include "strategy_goal_type.h"
#include "atomic_goal_type.h"

class MovingEntity;
class Node;

template<typename T>
class GoalEvaluator;

class ThinkGoal : public GoalComposite<MovingEntity> {
private:
    std::vector<GoalEvaluator<MovingEntity> *> _evaluators;
public:
    ThinkGoal(MovingEntity *);

    ~ThinkGoal();

    void add_evaluator(GoalEvaluator<MovingEntity> *);

    /**
     * calculate the most desirable goal, based on given evaluators.
     */
    void determine_next_goal();

    void set_goal_wander();

    void set_goal_follow_path();

    bool has_sub_goal(StrategyGoalType);

    bool has_atomic_goal(AtomicGoalType);

    void set_goal_work();

    void set_goal_combat(MovingEntity* = nullptr);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;

    /*!
     * Set the status of all sub_goals to failed
     */
    void failed_all_current_goals();

    /*!
     * Set the status of all sub_goals to active
     */
    void resume_sub_goals();

    Goal<MovingEntity>* initiate_goal(Goal<MovingEntity>* goal, int initiator);


};


#endif //C_AND_D_PROJECT_THINK_GOAL_H
