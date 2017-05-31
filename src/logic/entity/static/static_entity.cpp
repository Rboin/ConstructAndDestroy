//
// Created by Sander on 1-3-2017.
//

#include "graph/graph_manager.h"
#include "static_entity.h"
#include "graph/graph.h"
#include "matrix.h"
#include "entity/entity_types.h"

StaticEntity::StaticEntity(vec2 position, float mass) : BaseEntity(STATIC, position, mass) {
    // Remove edges from graph
    GraphManager *gm = GraphManager::get_instance();
    gm->setup({800, 600});
    gm->graph->remove_edge(position);

    // Set current node to unwalkable
    int node_index = gm->graph->get_node_with_position(position);
    Node* entity_node = gm->graph->nodes.at(node_index);
    entity_node->set_walkability(false);
};

/* Second constructor that doesn't expect an position,
 * because this will create a difference between static objects which
 * have been put hardcoded to the map and objects that have been put on the
 * map by the user.
 * The next constructor will be called when the user wants to add an object to the map.
 * It does not have a position yet, so no edges will be deleted from the graph, because
 * that would affect A*
 */
StaticEntity::StaticEntity(float mass) : BaseEntity(STATIC, {0,0}, mass) {
    GraphManager *gm = GraphManager::get_instance();
    gm->setup({800, 600});
};

void StaticEntity::set_position(float x, float y, bool finalposition) {
    // Call base method first, to set the position first
    BaseEntity::set_position(x, y);

    if(finalposition) {
        // Remove edges from graph
        GraphManager *gm = GraphManager::get_instance();
        gm->setup({800, 600});
        gm->graph->remove_edge(_position);

        // Set current node to unwalkable
        int node_index = gm->graph->get_node_with_position(_position);
        Node *entity_node = gm->graph->nodes.at(node_index);
        entity_node->set_walkability(false);
    }
}