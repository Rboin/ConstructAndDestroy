//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_MINER_ENTITY_H
#define C_AND_D_PROJECT_MINER_ENTITY_H

#include "moving_entity.h"

class MovingEntity;

class MinerEntity : public MovingEntity {
public:
    MinerEntity(const mesh *, vec2, float, const float, const float);
};


#endif //C_AND_D_PROJECT_MINER_ENTITY_H
