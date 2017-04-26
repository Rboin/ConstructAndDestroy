//
// Created by Sander on 2-3-2017.
//

#include "edge.h"

Edge::Edge(int f, int t, float c) {
    from = f;
    to = t;
    cost = c;
    active = true;
}

Edge::Edge(int f, int t) {
    from = f;
    to = t;
    cost = 1.0;
    active = true;
};

int Edge::get_cost() {
    return cost;
}

int Edge::get_from() {
    return from;
}

int Edge::get_to() {
    return to;
}

void Edge::set_active(bool a) {
    active = a;
}

bool Edge::is_active() {
    return active;
}

