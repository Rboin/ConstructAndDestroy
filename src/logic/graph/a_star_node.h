//
// Created by Sander on 9-3-2017.
//

#ifndef C_AND_D_PROJECT_A_STAR_NODE_H
#define C_AND_D_PROJECT_A_STAR_NODE_H


#include <types.h>
#include "node.h"

class AStarNode : public Node {
public:
    AStarNode(int, vec2, std::vector<Edge *>, int, int);
    ~AStarNode();
    AStarNode *parent;
    int f; //calculated total for A*
    int g; //Stepcost for A*
    int h; //Heuristic estimate
};


#endif //C_AND_D_PROJECT_A_STAR_NODE_H
