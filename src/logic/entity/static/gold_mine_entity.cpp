//
// Created by Stephan Schrijver on 15-5-2017.
//

#include "gold_mine_entity.h"

GoldMineEntity::GoldMineEntity(const mesh *base, vec2 position, float mass) : ResourceEntity(
        base, position, mass, GOLD) {
}