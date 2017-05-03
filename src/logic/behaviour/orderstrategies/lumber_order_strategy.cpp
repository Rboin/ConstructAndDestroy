#include "lumber_order_strategy.h"
#include <graph/graph_manager.h>
#include <graph/graph.h>
#include <iostream>
#include <entity/goal/moving_entity_goal/atomic/plan_path_goal.h>
#include <entity/static/resource_type.h>
#include <entity/static/resource_manager.h>
#include <entity/goal/moving_entity_goal/atomic/gather_resource_goal.h>
#include <entity/goal/moving_entity_goal/follow_path_goal.h>
#include "entity/goal/moving_entity_goal/think_goal.h"

bool LumberOrderStrategy::applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    return target && target->is(ResourceType::TREE);
}

void LumberOrderStrategy::execute(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    ResourceManager *rm = ResourceManager::get_instance();
    vec2 campfire_position = rm->get_closest_resource(targetVector, TREE);

    Graph* graph = GraphManager::get_instance()->graph;
    int goal = graph->get_node_with_exact_position(campfire_position);
    Node* resource = graph->nodes.at(goal);
    if (resource->get_index() == 0) {
        return;
    }
    Node* closestEdge = graph->find_closest_edge(resource);

    for(int i = 0; i < units->size(); i++){
        MovingEntity* selectedUnit = units->at(i);

        if (selectedUnit->job_type != JobType::ENEMY) {
            selectedUnit->get_brain()->remove_all_subgoals();
            selectedUnit->get_brain()->add_priority_subgoal(new PlanPathGoal(selectedUnit, closestEdge));
            selectedUnit->get_brain()->add_priority_subgoal(new FollowPathGoal(selectedUnit));
            selectedUnit->get_brain()->add_priority_subgoal(new GatherResourceGoal(selectedUnit, resource->get_position()));
        }
    }
}