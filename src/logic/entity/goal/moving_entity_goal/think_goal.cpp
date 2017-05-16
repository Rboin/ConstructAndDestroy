//
// Created by robin on 3/11/17.
//

#include "entity/goal/moving_entity_goal/atomic/obstacle_avoidance_goal.h"
#include "entity/goal/moving_entity_goal/atomic/traverse_edge_goal.h"
#include <iostream>
#include "think_goal.h"
#include "goal/goal_evaluator.h"
#include "vector.h"
#include "follow_path_goal.h"
#include "entity/goal/moving_entity_goal/atomic/wander_goal.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "work_goal.h"
#include "combat_goal.h"

ThinkGoal::ThinkGoal(MovingEntity *e) : GoalComposite(e, THINK) {
    status = ACTIVE;
    _evaluators = std::vector<GoalEvaluator<MovingEntity> *>();
}

Goal<MovingEntity>* ThinkGoal::initiate_goal(Goal<MovingEntity>* goal, int initiator) {
    goal->set_initiator(initiator);
    return goal;
}

void ThinkGoal::add_evaluator(GoalEvaluator<MovingEntity> *e) {
    _evaluators.push_back(e);
}

void ThinkGoal::determine_next_goal() {
    GoalEvaluator<MovingEntity> *best = nullptr;
    float score, best_score = 0;
    for (std::vector<GoalEvaluator<MovingEntity> *>::iterator it = _evaluators.begin(); it != _evaluators.end(); it++) {
        score = (*it)->calculate_desirability(owner);
        if (score > best_score) {
            best = (*it);
            best_score = score;
        }
    }

    if (best)
        best->set_goal(owner);
}

void ThinkGoal::set_goal_wander() {
    if (!has_atomic_goal(WANDER)) {
        add_subgoal(new WanderGoal(owner));
    }
}

void ThinkGoal::set_goal_obstacle_avoidance(vec2 *v) {
    if (!has_atomic_goal(OBSTACLE_AVOIDANCE)) {
        add_subgoal(new ObstacleAvoidanceGoal(owner, v));
    }
}

void ThinkGoal::set_goal_work() {
    if (!has_sub_goal(WORK)) {
        add_subgoal(new WorkGoal(owner));
    }
}

void ThinkGoal::set_goal_follow_path() {
    add_subgoal(new FollowPathGoal(owner));
}

void ThinkGoal::set_goal_combat() {
    if(!has_sub_goal(COMBAT)){
        add_subgoal(new CombatGoal(owner));
    }
}

bool ThinkGoal::has_sub_goal(StrategyGoalType sgt) {
    bool found = false;
    for (typename std::deque<Goal<MovingEntity> *>::iterator it = sub_goals.begin(); it != sub_goals.end(); it++) {
        Goal<MovingEntity> *current_goal = (*it);
        if (current_goal->get_type() == sgt) {
            found = true;
            break;
        }
    }
    return found;
}

bool ThinkGoal::has_atomic_goal(AtomicGoalType agt) {
    bool found = false;
    for (typename std::deque<Goal<MovingEntity> *>::iterator it = sub_goals.begin(); it != sub_goals.end(); it++) {
        Goal<MovingEntity> *current_goal = (*it);
        if (current_goal->get_type() == agt) {
            found = true;
            break;
        }
    }
    return found;
}

void ThinkGoal::activate() {
    status = ACTIVE;
}

const int ThinkGoal::process() {
    activate_if_inactive();

    determine_next_goal();

    return process_subgoals();
}

void ThinkGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

const char *ThinkGoal::get_name() const {
    return "Think";
}
