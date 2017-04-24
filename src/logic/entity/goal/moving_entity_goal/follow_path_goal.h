//
// Created by Sander on 14-3-2017.
//

#ifndef C_AND_D_PROJECT_FOLLOW_PATH_GOAL_H
#define C_AND_D_PROJECT_FOLLOW_PATH_GOAL_H

#include <vector>
#include <queue>
#include "types.h"
#include "goal/composite_goal.h"

class MovingEntity;

template<typename T>
class GoalEvaluator;

class FollowPathGoal : public GoalComposite<MovingEntity> {
private:
    std::vector<GoalEvaluator<MovingEntity> *> _evaluators;
public:
    FollowPathGoal(MovingEntity *);

    void add_evaluator(GoalEvaluator<MovingEntity> *);

    /**
     * calculate the most desirable goal, based on given evaluators.
     */
    void determine_next_goal();

    void set_goal_traverse_edge(vec2*);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};

#endif //C_AND_D_PROJECT_FOLLOW_PATH_GOAL_H
