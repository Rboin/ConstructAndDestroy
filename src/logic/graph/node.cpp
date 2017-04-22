//
// Created by Sander on 2-3-2017.
//

#include <vector>
#include "node.h"
#include "edge.h"

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

std::vector<Edge*> Node::get_neighbors() {
    return neighbors;
}

void Node::remove_edges() {
    for(int i = 0; i < neighbors.size(); i++){
        delete neighbors[i];
    }
    neighbors.clear();
}