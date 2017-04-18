//
// Created by robin on 3/4/17.
//

#include <gtest/gtest.h>
#include "tree/bsp_tree.h"
#include "tree/bsp_node.h"
#include "entity/static/static_entity.h"
#include "mesh.h"


TEST(BSPTree, Generate) {
    float width = 800, height = 600, min_width = 50, min_height = 50;
    BSPTree *tree = new BSPTree({width, height}, {min_width, min_height});
    ASSERT_GT(tree->size(), 1);
}

TEST(BSPTree, Insert) {
    float width = 800, height = 600, min_width = 50, min_height = 50;
    BSPTree *tree = new BSPTree({width, height}, {min_width, min_height});
    vec2 default_shape[] = {
            {-20, -20},
            {20,  -20},
            {20,  20},
            {-20, 20},
    };
    mesh base = {4, default_shape};
    BaseEntity e = StaticEntity(&base, {0, 400}, 1.0f, TextureTypes::CAMPFIRETEXTURE);
    ASSERT_NO_THROW(tree->insert(&e));
}

TEST(BSPTree, Find) {
    float width = 800, height = 600, min_width = 50, min_height = 50;
    BSPTree *tree = new BSPTree({width, height}, {min_width, min_height});
    vec2 default_shape[] = {
            {-20, -20},
            {20,  -20},
            {20,  20},
            {-20, 20},
    };
    mesh base = {4, default_shape};
    BaseEntity e = StaticEntity(&base, {780, 590}, 1.0f, TextureTypes::CAMPFIRETEXTURE);
    tree->insert(&e);
    bsp_node *node;
    ASSERT_NO_THROW(node = tree->find(e));
    ASSERT_TRUE(node);
    BaseEntity *b = node->entities.at(0);
    ASSERT_EQ(&e, b);
}

TEST(BSPTree, Remove) {
    float width = 800, height = 600, min_width = 50, min_height = 50;
    BSPTree *tree = new BSPTree({width, height}, {min_width, min_height});
    vec2 default_shape[] = {
            {-20, -20},
            {20,  -20},
            {20,  20},
            {-20, 20},
    };
    mesh base = {4, default_shape};
    BaseEntity e = StaticEntity(&base, {10, 400}, 1.0f, TextureTypes::CAMPFIRETEXTURE);
    tree->insert(&e);

    ASSERT_NO_THROW(tree->remove(&e));
    bsp_node *node = tree->find(e);
    for (int i = 0; i < node->entities.size(); i++) {
        ASSERT_NE(node->entities.at(i), &e);
    }
}
