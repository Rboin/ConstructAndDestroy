//
// Created by Sander on 2-3-2017.
//

#ifndef C_AND_D_PROJECT_GRAPH_H
#define C_AND_D_PROJECT_GRAPH_H

#include <vector>
#include "node.h"
#include "edge.h"
#include "list"
#include <SDL2/SDL.h>
#include <stack>
#include <queue>

class AStarNode;
class Graph {
private:
    bool show_graph;
    vec2 world_size;
public:
    std::vector<vec2 *> draw_path;

    Graph(vec2 world_size);
    std::vector<Node *> nodes;

    void generate_nodes();

    void generate_adjacency_edges();

    void remove_edge(vec2);

    void render(SDL_Renderer *);

    void set_show_graph();

    std::vector<vec2*> a_star_path(Node *, Node *);

    template <class T>
    T *in_list(std::vector<T *>, int);

    template <class T>
    void remove_from_list(std::vector<T *>&, T *);

    int manhattan_heuristic2(vec2 *, vec2 *);

    template <class T>
    T *get_best(std::vector<T *>);

    std::vector<vec2*> build_path(AStarNode*, std::vector<vec2*>&);

    int get_node_with_position(vec2);
};


#endif //C_AND_D_PROJECT_GRAPH_H
