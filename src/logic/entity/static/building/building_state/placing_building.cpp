//
// Created by Stephan Schrijver on 20-4-2017.
//

#include "entity/static/building/building_manager.h"
#include "graph/graph_manager.h"
#include "placing_building.h"
#include "entity/static/building/building_entity.h"
#include "entity/state/state_machine.h"
#include "entity/player.h"
#include "graph/graph.h"
#include "choosing_building_position.h"
#include "abort_placing_building.h"

void PlacingBuilding::enter(Player * p) {

    // Check if building can be placed on the current node
    GraphManager* gm = GraphManager::get_instance();
    int node_index = gm->graph->get_node_with_position(p->positioning_building->get_position());
    Node* curr_node = gm->graph->nodes.at(node_index);

    if(!curr_node->is_walkable()) {
        // Building should not be placed here, try to find another position
        p->state_machine->change_state(new ChoosingBuildingPosition());
    }

    else {
        if (p->resources->check_if_sufficient_resources(p->positioning_building->get_costs()))
        {
            p->positioning_building->set_transparent_or_border(false, false);
            // Set final position so it will affect the A*
            p->positioning_building->set_position(p->positioning_building->get_position().x,p->positioning_building->get_position().y, true);
            // Add building to building manager
            BuildingManager::get_instance()->add_building(p, p->positioning_building);

            p->resources->subtract_resources(p->positioning_building->get_costs());

            p->positioning_building = nullptr;
            p->state_machine->clear_state();
        }
        else
        {
            p->state_machine->change_state(new AbortPlacingBuilding());
        }
    }
}

void PlacingBuilding::execute(Player * ent) {
}


void PlacingBuilding::exit(Player * p) {

}
