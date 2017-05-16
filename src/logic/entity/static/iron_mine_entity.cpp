//
// Created by Sander on 4-4-2017.
//

#include "iron_mine_entity.h"

IronMineEntity::IronMineEntity(const mesh *base, vec2 position, float mass) : ResourceEntity(
        base, position, mass, IRON) {
}