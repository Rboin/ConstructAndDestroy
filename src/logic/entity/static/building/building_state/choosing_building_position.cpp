//
// Created by Stephan Schrijver on 19-4-2017.
//

#include "SDL_mouse.h"
#include "neighbourhood/neighbourhood_manager.h"
#include "graph/graph_manager.h"
#include "graph/graph.h"
#include "world/world.h"
#include "choosing_building_position.h"
#include "entity/static/building/building_entity.h"
#include "entity/player.h"

void ChoosingBuildingPosition::enter(Player *p) {


    // Set to transparent object
    p->positioning_object->set_transparent_or_border(true);
}

void ChoosingBuildingPosition::execute(Player *p) {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    // Check if mouse position is different
    // because if not, it will not have to check if the building
    // is colliding with other objects in the game
    if (x != previous_mouse_x || y != previous_mouse_y) {
        // Reset previous mouse position with current values
        previous_mouse_x = x;
        previous_mouse_y = y;

        /*
         * UNCOMMENT BELOW TO SET OBJECT TO MOUSE POSITION
         * IT IS POSSIBLE THAT OBJECTS ARE OVERLAPPING
         *
         * // Calculate the object its position if you want the mouse to be the
         * // center of the object.
         *
         * int new_obj_x = x - (p->positioning_object->get_representation()->get_size()->x /2);
         * int new_obj_y = y - (p->positioning_object->get_representation()->get_size()->y /2);
         *
         * p->positioning_object->set_position(new_obj_x, new_obj_y, false);
         *
         * UNCOMMENT UNTIL HERE TO SET OBJECT TO MOUSE POSITION
        */


        GraphManager *gm = GraphManager::get_instance();
        int node_index = gm->graph->get_node_with_position({x, y});
        Node *curr_node = gm->graph->nodes.at(node_index);

        float new_obj_x = curr_node->get_position()->x;
        float new_obj_y = curr_node->get_position()->y;
        p->positioning_object->set_position(new_obj_x, new_obj_y, false);

        if (!curr_node->is_walkable()) {
            // This node is not walkable, so set to other texture!
            p->positioning_object->set_transparent_or_border(true, false);
        } else {
            p->positioning_object->set_transparent_or_border(true);
        }
    }
}


void ChoosingBuildingPosition::exit(Player *p) {
}
