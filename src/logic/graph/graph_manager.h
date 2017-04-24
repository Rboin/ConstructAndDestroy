//
// Created by Sander on 12-3-2017.
//

#ifndef C_AND_D_PROJECT_GRAPH_MANAGER_H
#define C_AND_D_PROJECT_GRAPH_MANAGER_H

#include <vector>
#include "types.h"

class Graph;

class Node;

class AStarNode;

class Edge;


class GraphManager {
private:

    GraphManager();

    static GraphManager *instance;
public:
    ~GraphManager();

    void setup(vec2);

    static GraphManager *get_instance();

    Graph *graph;

};


#endif //C_AND_D_PROJECT_GRAPH_MANAGER_H
