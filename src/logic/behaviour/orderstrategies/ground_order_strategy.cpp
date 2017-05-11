#include "graph/graph_manager.h"
#include "graph/graph.h"
#include "entity/goal/moving_entity_goal/follow_path_goal.h"
#include "ground_order_strategy.h"
#include "entity/goal/moving_entity_goal/think_goal.h"

bool GroundOrderStrategy::applies(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    // when target is nullptr then the user clicked on the ground
    return target == nullptr;
}

void GroundOrderStrategy::execute(std::vector<MovingEntity *> *units, vec2 &targetVector, BaseEntity *target) {
    Graph* graph = GraphManager::get_instance()->graph;
    int goal = graph->get_node_with_position(targetVector);
    goal = graph->find_closest_edge(graph->nodes[goal])->get_index();
    for(int i = 0; i < units->size(); i++){
        MovingEntity* selectedUnit = units->at(i);

        if (selectedUnit->job_type != JobType::ENEMY) {
            int start = graph->get_node_with_position(selectedUnit->get_position());
            std::vector<vec2 *> path = graph->a_star_path(graph->nodes[start], graph->nodes[goal]);

            selectedUnit->get_brain()->remove_all_subgoals();
            selectedUnit->path = path;
            selectedUnit->get_brain()->add_subgoal(new FollowPathGoal(selectedUnit, Initiator::PLAYER));
        }
    }
}