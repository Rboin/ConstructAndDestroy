//
// Created by Sander on 4-4-2017.
//

#include "lumberjack_entity.h"

LumberJackEntity::LumberJackEntity(const mesh *base, vec2 position, float mass,
                                   const float max_force, const float max_speed) : MovingEntity(base, position, mass,
                                                                                                LUMBERJACKTEXTURE, max_force,
                                                                                                max_speed, WOODCUTTER) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
}