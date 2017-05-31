//
// Created by Sander on 2-3-2017.
//

#include <SDL_render.h>
#include <queue>
#include <cmath>
#include <stack>
#include <limits>
#include <cfloat>
#include "graph.h"
#include "a_star_node.h"

Graph::Graph(vec2 world_s) {
    _world_size = world_s;
    generate_nodes();
    generate_adjacency_edges();
}

Graph::~Graph() {
    for(int i = 0; i < nodes.size(); i++){
        delete nodes.at(i);
    }
    nodes.clear();
}

void Graph::generate_nodes() {
    nodes.reserve(300);
    int index = 0;
    for (int row = 0; row < _world_size.y; row += 40) {
        for (int column = 0; column < _world_size.x; column += 40) {
            Node *node = new Node(index, {(float) column, (float) row});
            nodes.emplace_back(node);
            index++;
        }
    }
}

void Graph::generate_adjacency_edges() {
    int index = 0;
    for (int row = 0; row < _world_size.y; row += 40) {
        for (int column = 0; column < _world_size.x; column += 40) {
            //don't add edges top when this is a node of the top row
            if (row != 0) {
                Edge *e1 = new Edge(index, index - 20);
                nodes.at(index)->add_neighbors(e1);
                //add edge to top left
                if (column != 0) {
                    Edge *v1 = new Edge(index, index - 21);
                    nodes.at(index)->add_neighbors(v1);
                }
                //add edge to top right
                if (column != 760) {
                    Edge *v2 = new Edge(index, index - 19);
                    nodes.at(index)->add_neighbors(v2);
                }
            }
            //don't add edges below when this is the last node of a row
            if (row != 560) {
                Edge *e2 = new Edge(index, index + 20);
                nodes.at(index)->add_neighbors(e2);
                //add edge to bottom left
                if (column != 0) {
                    Edge *v3 = new Edge(index, index + 19);
                    nodes.at(index)->add_neighbors(v3);
                }
                //add edge to bottom right
                if (column != 760) {
                    Edge *v4 = new Edge(index, index + 21);
                    nodes.at(index)->add_neighbors(v4);
                }
            }
            //don't add edges left when this is the first node of a column
            if (column != 0) {
                Edge *e3 = new Edge(index, index - 1);
                nodes.at(index)->add_neighbors(e3);
            }
            //don't add edges right when this is the last node of a column
            if (column != 760) {
                Edge *e4 = new Edge(index, index + 1);
                nodes.at(index)->add_neighbors(e4);
            }
            index++;
        }
    }
}

void Graph::remove_edge(vec2 edge) {
    int index = 0;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->get_position()->x == edge.x && nodes[i]->get_position()->y == edge.y) {
            index = i;
            break;
        }
    }
    if (index)
        nodes[index]->remove_edges();

}

std::stack<vec2 *> Graph::a_star_path(Node *start, Node *end) {
    std::stack<vec2 *> path;
    AStarNode *neighbor;
    std::vector<AStarNode *> open_list;
    std::vector<AStarNode *> closed_list;
    int step_cost = 0;
    //add start point to openlist
    AStarNode *current = new AStarNode(start->get_index(), start->get_position()->clone(), start->get_neighbors(),
                                       step_cost,
                                       manhattan_heuristic(start->get_position(), end->get_position()));
    open_list.emplace_back(current);

    while (open_list.size() != 0) {
        current = get_best(open_list);

        //check if end is reached
        if (current->get_index() == end->get_index()) {
            path = build_path(current, path);
            return path;
        }

        //move current into closed set
        remove_from_list(open_list, current);
        closed_list.emplace_back(current);

        //check all the neighbors
        for (int i = 0; i < current->get_neighbors().size(); i++) {
            //check whether the current edge/neighbor is active, otherwise we can skip this iteration.
            if (!current->get_neighbors()[i]->is_active())
                continue;
            //get current step and distance from current to neighbor
            step_cost = current->g + manhattan_heuristic(current->get_position(),
                                                          nodes[current->get_neighbors()[i]->get_to()]->get_position());

            // Check for the neighbor in the closed set
            // then see if its cost is >= the stepCost, if so skip current neighbor
            neighbor = in_list(closed_list, nodes[current->get_neighbors()[i]->get_to()]->get_index());
            if (neighbor && step_cost >= neighbor->g) {
                continue;
            }
            // Verify neighbor doesn't exist or new score for it is better
            neighbor = in_list(open_list, nodes[current->get_neighbors()[i]->get_to()]->get_index());
            if (!neighbor || step_cost < neighbor->g) {
                if (!neighbor) {
                    Node *temp = nodes[current->get_neighbors()[i]->get_to()];
                    neighbor = new AStarNode(temp->get_index(), temp->get_position()->clone(),
                                             temp->get_neighbors(),
                                             step_cost,
                                             manhattan_heuristic(temp->get_position(), end->get_position()));
                    neighbor->parent = current;
                    open_list.emplace_back(neighbor);
                } else {
                    neighbor->parent = current;
                    neighbor->g = step_cost;
                    neighbor->f = step_cost + neighbor->h;
                }
            }
        }
    }
    return path;
}

template<class T>
T *Graph::get_best(std::vector<T *> list) {
    int best = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->f < list[best]->f) {
            best = i;
        }
    }
    return list[best];
}

int Graph::manhattan_heuristic(vec2 *current, vec2 *end) {
    int cost_x = std::abs((current->x / 40) - (end->x / 40));
    int cost_y = std::abs((current->y / 40) - (end->y / 40));

    if (cost_x > cost_y) {
        return 14 * cost_y + 10 * (cost_x - cost_y);
    }
    return 14 * cost_x + 10 * (cost_y - cost_x);
};

template<class T>
T *Graph::in_list(std::vector<T *> list, int index) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->get_index() == index) {
            return list[i];
        }
    }
}

template<class T>
void Graph::remove_from_list(std::vector<T *> &list, T *node) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->get_index() == node->get_index()) {
            list.erase(list.begin() + i);
        }
    }
}

std::stack<vec2 *> Graph::build_path(AStarNode *node, std::stack<vec2 *> &path) {
    path.push(node->get_position());
    if (node->parent) {
        return build_path(node->parent, path);
    } else {
        return path;
    }
}

int Graph::get_node_with_position(vec2 pos) {
    float closest_cost = DBL_MAX;
    int closest_node = 0;
    for (int i = 0; i < nodes.size(); i++) {
        float distance = pos.distance_squared(nodes.at(i)->get_position()->clone());

        if(distance < closest_cost){
            closest_cost = distance;
            closest_node = nodes.at(i)->get_index();
        }

    }
    return closest_node;
}

int Graph::get_node_with_exact_position(vec2 pos) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes.at(i)->get_position()->x == pos.x && nodes.at(i)->get_position()->y == pos.y) {
            return nodes.at(i)->get_index();
        }
    }
}

Node *Graph::find_closest_edge(Node * node) {
    int j = 0;
    for (int i = node->get_index(); i < 300; i++) {
        j++;
        //right of current node
        for (int k = 0; k < nodes[i]->get_neighbors().size(); k++) {
            if (nodes[i]->get_neighbors().at(k)->is_active()) {
                return nodes[i];
            }
            //left of current node
            if (nodes[i - j]->get_neighbors().at(k)->is_active()) {
                return nodes[i - j];
            }
        }
    }
}

