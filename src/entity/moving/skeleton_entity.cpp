//
// Created by Sander on 6-4-2017.
//

#include "skeleton_entity.h"

SkeletonEntity::SkeletonEntity(const mesh *base, vec2 position, float mass,
                                   const float max_force, const float max_speed) : MovingEntity(base, position, mass,
                                                                                                AXETEXTURE, max_force,
                                                                                                max_speed, ENEMY) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
}