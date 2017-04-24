//
// Created by Sander on 4-4-2017.
//

#include "miner_entity.h"

MinerEntity::MinerEntity(const mesh *base, vec2 position, float mass,
                                   const float max_force, const float max_speed) : MovingEntity(base, position, mass,
                                                                                                            MINERTEXTURE, max_force,
                                                                                                            max_speed, MINER) {
    carrying = 0;
    tiredness = 0;
    hunger = 0;
}