//
// Created by Sander on 4-4-2017.
//

#include "tree_entity.h"
#include "resource_entity.h"

TreeEntity::TreeEntity(const mesh *base, vec2 position, float mass) : ResourceEntity(
        base, position, mass, TREE) {
}
