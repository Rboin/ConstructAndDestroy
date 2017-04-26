//
// Created by Sander on 2-3-2017.
//

#ifndef C_AND_D_PROJECT_GRAPH_NODE_H
#define C_AND_D_PROJECT_GRAPH_NODE_H

#include <types.h>
#include <vector>
#include "vector.h"

class Edge;

class Node {
protected:
    int index;
    vec2 position;
    std::vector<Edge *> neighbors;
public:
    Node(int, vec2);

    virtual vec2 *get_position();

    virtual int get_index();

    virtual std::vector<Edge*> get_neighbors();

    virtual void add_neighbors(Edge *);

    void remove_edges();

    void remove_edge(int,int);
};

#endif //C_AND_D_PROJECT_GRAPH_NODE_H
