//
// Created by Sander on 10-5-2017.
//

#include <iostream>
#include <cfloat>
#include "entity/moving/knight_entity.h"
#include "settings.h"
#include "graph/graph.h"
#include "entity/goal/moving_entity_goal/atomic/fight_goal.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "combat_goal.h"
#include "think_goal.h"
#include "follow_path_goal.h"
#include "behaviour/behaviour.h"
#include "hunt_target_goal.h"

CombatGoal::CombatGoal(MovingEntity *e, MovingEntity *enemy) : GoalComposite(e, COMBAT) {
    if (!enemy) {
        PlayerManager *pm = PlayerManager::get_instance();

        Player *enemy_player;
        if (owner->get_player()->get_id() == computer_id) {
            enemy_player = pm->get_player(player_id);
        } else {
            enemy_player = pm->get_player(computer_id);
        }

        if (!enemy_player->units.empty()) {
            ///If there is an knight attack that first
            MovingEntity *enemy_entity = enemy_player->get_combat_unit();
            if (enemy_entity) {
                _enemy = enemy_entity;
            } else {
                _enemy = enemy_player->units.front();
            }


            set_goal_hunt_target();
            set_goal_attack_enemy();
        }
        else if (!enemy_player->buildings.empty()) {
            set_goal_move_to_building(enemy_player);
            set_goal_attack_building();
        }
        //No enemy found so goal is completed
        else {
            status = COMPLETED;
        }
    } else {
        _enemy = enemy;
        set_goal_attack_enemy();
    }
}

CombatGoal::~CombatGoal() {
    remove_all_subgoals();
    _building = nullptr;
    _enemy = nullptr;
}

void CombatGoal::set_goal_hunt_target() {
    float distance_to_enemy = _enemy->get_position().distance(owner->get_position());
    if (distance_to_enemy < 40) {
        //fight
        if (!_enemy->is_engaged()) {
            _enemy->set_engaged(true);
            _enemy->get_brain()->remove_all_subgoals();
            _enemy->get_brain()->set_goal_combat(owner);
        }
    } else {
        this->sub_goals.push_front(new HuntTargetGoal(owner, _enemy));
    }
}

void CombatGoal::set_goal_attack_enemy() {
    this->sub_goals.push_front(new FightGoal(owner, _enemy));
}


void CombatGoal::set_goal_move_to_building(Player *enemy_player) {
    float closest = DBL_MAX;
    for (int i = 0; i < enemy_player->buildings.size(); i++) {
        float distance = owner->get_position().distance(enemy_player->buildings.at(i)->get_position());
        if (distance < closest) {
            closest = distance;
            _building = enemy_player->buildings.at(i);
        }
    }


//    float distance_to_enemy = _enemy->get_position().distance(owner->get_world_translation());
    if (closest > 40) {
        this->sub_goals.push_front(new HuntTargetGoal(owner, _building));
    }
}

void CombatGoal::set_goal_attack_building() {
    this->sub_goals.push_front(new FightGoal(owner, _building));
}

void CombatGoal::activate() {
    status = ACTIVE;
}

const int CombatGoal::process() {
    activate_if_inactive();
    status = process_subgoals();

    if (sub_goal_is_completed(HUNTTARGET)) {
        terminate();
    }

    return status;
}

void CombatGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

const char *CombatGoal::get_name() const {
    return "Combat";
}

bool CombatGoal::sub_goal_is_completed(StrategyGoalType agt) {
    for (typename std::deque<Goal<MovingEntity> *>::iterator it = sub_goals.begin(); it != sub_goals.end(); it++) {
        Goal<MovingEntity> *current_goal = (*it);
        if (current_goal->get_type() == agt) {
            return current_goal->get_status() == COMPLETED;
        }
    }
}
