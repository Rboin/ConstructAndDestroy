//
// Created by robin on 3/4/17.
//

#ifndef C_AND_D_PROJECT_BSP_TREE_H
#define C_AND_D_PROJECT_BSP_TREE_H

#include "types.h"

class BaseEntity;

struct bsp_node;

class BSPTree {
private:
    bsp_node *root;

    void clear_node(bsp_node *);

    int size(bsp_node *);

    static void insert(bsp_node *, BaseEntity *, bool);

    static bsp_node *find(bsp_node *, const vec2 &, int depth = -1, bool vertical = true);

    bsp_node *generate_subtree(vec2, vec2, vec2, bool);

    void generate(vec2, vec2);

public:
    BSPTree(vec2, vec2);

    ~BSPTree();

    int size();

    void insert(BaseEntity *);

    static void insert_at(bsp_node *, BaseEntity *);

    void remove(BaseEntity *);

    static void remove_from(bsp_node *, BaseEntity &);

    bsp_node *find(BaseEntity &);

    bsp_node *find(const vec2 &);

    bsp_node *find_at_depth(BaseEntity &, int);

    static bsp_node *find_from(bsp_node *, const vec2 &);

};


#endif //C_AND_D_PROJECT_BSP_TREE_H
