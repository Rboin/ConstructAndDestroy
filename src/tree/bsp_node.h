//
// Created by robin on 3/4/17.
//

#ifndef C_AND_D_PROJECT_NSP_NODE_H
#define C_AND_D_PROJECT_NSP_NODE_H

#define BOUND_SIZE 4

#include <vector>
#include "types.h"

class BaseEntity;

struct bsp_node {

    vec2 *bounds;
    std::vector<BaseEntity*> entities;
    bsp_node *left, *right;
};

#endif //C_AND_D_PROJECT_NSP_NODE_H
