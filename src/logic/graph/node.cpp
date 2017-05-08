//
// Created by Sander on 2-3-2017.
//

#include <vector>
#include "node.h"
#include "edge.h"
#include "graph_manager.h"
#include "graph.h"

Node::Node(int i, vec2 v) {
    index = i;
    position = v;
}

void Node::add_neighbors(Edge *e) {
    neighbors.emplace_back(e);
}

vec2 *Node::get_position() {
    return &position;
}

int Node::get_index() {
    return index;
}

std::vector<Edge *> Node::get_neighbors() {
    return neighbors;
}

//void Node::remove_edges() {
//    for(int i = 0; i < neighbors.size(); i++){
//        delete neighbors[i];
//    }
//    neighbors.clear();
//}

void Node::remove_edges() {
    for(int i = 0 ;  i < neighbors.size(); i++){
        remove_edge(neighbors[i]->get_to(),this->index);
        neighbors[i]->set_active(false);
    }
}

void Node::remove_edge(int f, int to) {
    GraphManager *gm = GraphManager::get_instance();
    Node* from = gm->graph->nodes[f];
    for(int i = 0 ; i < from->neighbors.size(); i++){
        if(from->neighbors[i]->get_to() == to){
            from->neighbors[i]->set_active(false);
            break;
        }
    }
}

bool Node::is_walkable() {
    return walkable;
}

bool Node::set_walkability(bool b) {
    walkable = b;
}