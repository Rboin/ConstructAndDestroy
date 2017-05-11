//
// Created by Sander on 10-5-2017.
//

#include "entity/player_manager.h"
#include "entity/player.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "combat_goal.h"
#include "strategy_goal_type.h"
#include "follow_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "behaviour/behaviour.h"
#include "hunt_target_goal.h"

CombatGoal::CombatGoal(MovingEntity *e) : GoalComposite(e, COMBAT) {
    set_goal_hunt_target();
}

void CombatGoal::set_goal_hunt_target() {
        this->sub_goals.push_front(new HuntTargetGoal(owner));
}

void CombatGoal::set_goal_attack_enemy() {
}

void CombatGoal::activate() {
    status = ACTIVE;
}

const int CombatGoal::process() {
    activate_if_inactive();
    status = process_subgoals();

    return status;
}

void CombatGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

const char *CombatGoal::get_name() const {
    return "Combat";
}
