//
// Created by Sander on 4-4-2017.
//

#include "campfire_entity.h"

CampfireEntity::CampfireEntity(const mesh *base, vec2 position, float mass) : ResourceEntity(
        base, position, mass, CAMPFIRE) {
}