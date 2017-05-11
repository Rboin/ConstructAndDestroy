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
    vec2 world_size;
public:
    std::vector<vec2 *> draw_path;

    Graph(vec2 world_size);
    std::vector<Node *> nodes;

    void generate_nodes();

    /*!
     * Generates edges for all nodes in the graph. A node can have a maximum of 8 edges.
     */
    void generate_adjacency_edges();

    void remove_edge(vec2);

    void render(SDL_Renderer *);

    /*!
     * Calculates the a star path using manhattan heuristic.
     */
    std::stack<vec2*> a_star_path(Node *, Node *);

    /*!
     * Checks if a node with the given index is in the current vector
     * @return the node if found, other nothing is returned;
     */
    template <class T>
    T *in_list(std::vector<T *>, int);

    /*!
     * Removes the given node from the given vector
     */
    template <class T>
    void remove_from_list(std::vector<T *>&, T *);

    /*!
     * Calculates the cost from position A to position B using the manhattan heuristic
     * Vertical and horizontal nodes cost 10 and diagonal nodes cost 14
     */
    int manhattan_heuristic(vec2 *, vec2 *);

    /*!
     * @return the node with the lowest cost
     */
    template <class T>
    T *get_best(std::vector<T *>);

    /*!
     * Recursive function that builds the path for a star
     * @return a stack with positions
     */
    std::stack<vec2*> build_path(AStarNode*, std::stack<vec2*>&);

    /*!
     * This function returns a node that is close to the given position
     */
    int get_node_with_position(vec2);

    /*!
     * This function return a node that matches the given position
     */
    int get_node_with_exact_position(vec2 pos);

    /*!
     * This function prevents that entities will get stuck in resource entities.
     * @return the closest node that has active edges/neighbors so a path can be planned.
     */
    Node* find_closest_edge(Node * node);
};


#endif //C_AND_D_PROJECT_GRAPH_H
