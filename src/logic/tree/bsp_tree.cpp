//
// Created by robin on 3/4/17.
//

#include "vector.h"
#include "bsp_tree.h"
#include "bsp_node.h"
#include "entity/base_entity.h"

BSPTree::BSPTree(vec2 v1, vec2 v2) {
    generate(v1, v2);
}

BSPTree::~BSPTree() {
    clear_node(root);
    delete root;
}

void BSPTree::clear_node(bsp_node *node) {
    if (!node)
        return;
    clear_node(node->left);
    delete node->left;
    clear_node(node->right);
    delete node->right;
    delete[] node->bounds;
}

bsp_node *BSPTree::generate_subtree(vec2 pos, vec2 max, vec2 size, bool horizontal) {
    if (max.x - pos.x <= size.x || max.y - pos.y <= size.y)
        return 0;

//    int max_x = x + width,
//            max_y = y + height;
    vec2 *bounds = new vec2[BOUND_SIZE]{
            {pos.x, pos.y},
            {max.x, pos.y},
            {max.x, max.y},
            {pos.x, max.y}
    };
    bsp_node *node = new bsp_node;
    node->bounds = bounds;

    // Split the plane horizontally if true.
    if (horizontal) {
        vec2 max_v = {max.x, (pos.y + max.y) / 2};
        node->left = generate_subtree(pos, max_v, size, false);
        node->right = generate_subtree({pos.x, max_v.y}, max, size, false);
    } else {
        vec2 max_h = {(pos.x + max.x) / 2, max.y};
        node->left = generate_subtree(pos, max_h, size, true);
        node->right = generate_subtree({max_h.x, pos.y}, max, size, true);
    }
    return node;
}

void BSPTree::generate(vec2 max_size, vec2 min_size) {
    vec2 *root_bounds = new vec2[BOUND_SIZE]{
            {0,          0},
            {max_size.x, 0},
            {max_size.x, max_size.y},
            {0,          max_size.y}
    };
    bsp_node *_root = new bsp_node;
    _root->bounds = root_bounds;

    _root->left = generate_subtree({0, 0}, {max_size.x / 2, max_size.y}, min_size, true);
    _root->right = generate_subtree({max_size.x / 2, 0}, {max_size.x, max_size.y}, min_size, true);
    root = _root;
}

int BSPTree::size() {
    return size(root);
}

int BSPTree::size(bsp_node *node) {
    if (!node)
        return 0;
    return 1 + size(node->left) + size(node->right);
}

void BSPTree::insert(BaseEntity *e) {
    BSPTree::insert(root, e, true);
}

void BSPTree::insert_at(bsp_node *node, BaseEntity *entity) {
    BSPTree::insert(node, entity, true);
}

void BSPTree::insert(bsp_node *node, BaseEntity *entity, bool horizontal) {
    // If we've reached the lowest tree depth, insert.
    if (!node->left && !node->right) {
        node->entities.push_back(entity);
        return;
    }

    float hyp_x, hyp_y;

    vec2 pos = entity->get_position();

    // Determine whether we split vertically or horizontally.
    // This determines if we should take the X or Y coordinate to compare.
    if (horizontal) {
        hyp_x = node->bounds[1].x / 2;

        if (pos.x < hyp_x)
            insert(node->left, entity, !horizontal);
        else
            insert(node->right, entity, !horizontal);
    } else {
        hyp_y = node->bounds[2].y / 2;

        if (pos.y < hyp_y)
            insert(node->left, entity, !horizontal);
        else
            insert(node->right, entity, !horizontal);
    }
}

bsp_node *BSPTree::find(BaseEntity &e) {
    return BSPTree::find(root, e.get_position());
}

bsp_node *BSPTree::find(const vec2 &v) {
    return BSPTree::find(root, v);
}

bsp_node *BSPTree::find_from(bsp_node *node, const vec2 &v) {
    return BSPTree::find(node, v);
}

bsp_node *BSPTree::find(bsp_node *node, const vec2 &v, int depth, bool vertical) {
    if ((!node->left && !node->right) || depth == 0)
        return node;

    float hyp_x, hyp_y;

    bsp_node *result;
    // Determine whether we split vertically or horizontally.
    // This determines if we should take the X or Y coordinate to compare.
    if (vertical) {
        hyp_x = node->bounds[0].x + (node->bounds[1].x - node->bounds[0].x) / 2;

        if (v.x < hyp_x)
            result = find(node->left, v, depth - 1, !vertical);
        else
            result = find(node->right, v, depth - 1, !vertical);
    } else {
        hyp_y = node->bounds[0].y + (node->bounds[2].y - node->bounds[0].y) / 2;

        if (v.y < hyp_y)
            result = find(node->left, v, depth - 1, !vertical);
        else
            result = find(node->right, v, depth - 1, !vertical);
    }
    return result;
}

void BSPTree::remove(BaseEntity *e) {
    bsp_node *node = find(e->get_position());
    int index = -1;
    for (unsigned int i = 0; i < node->entities.size(); i++) {
        if (node->entities.at(i) == e) {
            index = i;
            break;
        }
    }
    if (index > -1) {
        node->entities.erase(node->entities.begin() + index);
    }
}

void BSPTree::remove_from(bsp_node *n, BaseEntity &e) {
    bsp_node *node = BSPTree::find_from(n, e.get_position());
    if (node) {
        int index = -1;
        for (unsigned int i = 0; i < node->entities.size(); i++) {
            BaseEntity *cur = node->entities.at(i);
            if (cur == &e) {
                index = i;
                break;
            }
        }
        if (index > -1) {
            node->entities.erase(node->entities.begin() + index);
        }
    }
}

bsp_node *BSPTree::find_at_depth(BaseEntity &e, int depth) {
    return find(root, e.get_position(), depth);
}
