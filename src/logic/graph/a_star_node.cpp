//
// Created by Sander on 9-3-2017.
//

#include <vector.h>
#include "a_star_node.h"

AStarNode::AStarNode(int i, vec2 v, std::vector<Edge*> neighbor, int a, int b) : Node(i,v) {
    neighbors = neighbor;
    f = a + b;
    g = a;
    h = b;
    parent = nullptr;
}

AStarNode::~AStarNode() {
    parent = nullptr;
}
