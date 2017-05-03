//
// Created by robin on 3/8/17.
//

#include <mesh.h>
#include <world/world.h>
#include "neighbourhood_manager.h"
#include "vector.h"
#include "tree/bsp_tree.h"
#include "tree/bsp_node.h"
#include "sorting/quicksort_strategy.h"
#include "entity/base_entity.h"

NeighbourhoodManager *NeighbourhoodManager::instance = nullptr;

NeighbourhoodManager::NeighbourhoodManager() {
    tree = nullptr;
    sorter = new QuicksortStrategy();
}

NeighbourhoodManager::~NeighbourhoodManager() {
    if (tree)
        delete tree;
    delete sorter;
}

void NeighbourhoodManager::setup(vec2 world_size, vec2 tile_size) {
    if (tree)
        delete tree;
    tree = new BSPTree(world_size, tile_size);
}

NeighbourhoodManager *NeighbourhoodManager::get_instance() {
    if (!instance)
        instance = new NeighbourhoodManager();
    return instance;
}

std::vector<BaseEntity *> NeighbourhoodManager::get_neighbours(BaseEntity *b) const {
    bsp_node *node = tree->find(b->get_position());
    return sorter->sort(b, node->entities);
}

BaseEntity *NeighbourhoodManager::get_closest_to(vec2 v) {
    // TODO: enable BSP tree optimalization again
    // currently entities can be within multiple partitions
    // but the BSP does not support this scenario yet
    // a workaround is to iterate over all entities to find the entity that
    // a player has clicked on
    // bsp_node *node = tree->find(v);
    // std::vector<BaseEntity *> closest = sorter->sort(v, node->entities);
    std::vector<BaseEntity *> closest = World::get_instance()->getEntities();
    if(closest.size() > 0) {
        for(int i = 0; i < closest.size(); i++) {
            BaseEntity *closest_to_v = closest.at(i);
            if (closest_to_v->get_bounds()->contains(v))
                return closest_to_v;
        }
    }
    return nullptr;
}

void NeighbourhoodManager::update(BaseEntity *b) {
    tree->remove(b);
    tree->insert(b);
}

void NeighbourhoodManager::insert(BaseEntity *b) {
    tree->insert(b);
}
