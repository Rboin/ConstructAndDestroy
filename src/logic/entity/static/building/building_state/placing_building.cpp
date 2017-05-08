//
// Created by Stephan Schrijver on 20-4-2017.
//

#include <entity/static/building/building_manager.h>
#include <graph/graph_manager.h>
#include "placing_building.h"
#include "entity/static/building/building_entity.h"
#include "entity/state/state_machine.h"
#include "entity/player.h"
#include "graph/graph.h"
#include "choosing_building_position.h"

void PlacingBuilding::enter(Player * p) {

    // Check if building can be placed on the current node
    GraphManager* gm = GraphManager::get_instance();
    int node_index = gm->graph->get_node_with_position(p->positioning_object->get_position());
    Node* curr_node = gm->graph->nodes.at(node_index);

    if(!curr_node->is_walkable()) {
        // Building should not be placed here, try to find another position
        p->state_machine->change_state(new ChoosingBuildingPosition());
    }

    else {
        p->positioning_object->set_to_transparent(false);
        // Set final position so it will affect the A*
        p->positioning_object->set_position(p->positioning_object->get_position().x,p->positioning_object->get_position().y, true);
        // Add building to building manager
        BuildingManager::get_instance()->add_building(p, p->positioning_object);

        p->positioning_object = nullptr;

        // Clear the state machine
        p->state_machine->clear_state();
    }
}

void PlacingBuilding::execute(Player * ent) {
}


void PlacingBuilding::exit(Player *) {

}
