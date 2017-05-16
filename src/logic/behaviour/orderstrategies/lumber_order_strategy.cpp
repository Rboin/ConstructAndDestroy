#include "entity/goal/moving_entity_goal/work_goal.h"
#include "lumber_order_strategy.h"
#include "iostream"
#include "entity/static/tree_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

bool LumberOrderStrategy::applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    if (target == nullptr) {
        return false;
    }

    if (dynamic_cast<TreeEntity *>(target)) {
        return true;
    }

    return false;
}

void LumberOrderStrategy::execute(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    for(int i = 0; i < units->size(); i++){
        MovingEntity* selectedUnit = units->at(i);

        if (selectedUnit->job_type != JobType::ENEMY) {
            selectedUnit->get_brain()->remove_all_subgoals();
            selectedUnit->get_brain()->add_subgoal(new WorkGoal(selectedUnit, &targetVector, Initiator::PLAYER));
        }
    }
}