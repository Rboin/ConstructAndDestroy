//
// Created by Sander on 10-5-2017.
//

#include "entity/player_manager.h"
#include "settings.h"
#include "combat_evaluator.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "entity/moving/moving_entity.h"
#include "entity/player.h"

const float CombatEvaluator::calculate_desirability(MovingEntity *t) {
    PlayerManager *pm = PlayerManager::get_instance();

    Player *enemy_player;
    if (t->get_player()->get_id() == computer_id) {
        enemy_player = pm->get_player(player_id);
    } else {
        enemy_player = pm->get_player(computer_id);
    }

    ///Enemy found so this goal has a high desirability
    if (!enemy_player->units.empty() || !enemy_player->buildings.empty()) {
        return 0.5;
    }

    return 0.0;

}

void CombatEvaluator::set_goal(MovingEntity *t) {
    t->get_brain()->set_goal_combat();
}
