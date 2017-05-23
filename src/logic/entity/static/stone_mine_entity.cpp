//
// Created by Stephan Schrijver on 23-5-2017.
//
#include "stone_mine_entity.h"
#include "mesh.h"

StoneMineEntity::StoneMineEntity(const mesh *base, vec2 position, float mass) : ResourceEntity(
        base, position, mass, STONE) {
}