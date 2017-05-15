//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_MINER_ENTITY_H
#define C_AND_D_PROJECT_MINER_ENTITY_H

#include "moving_entity.h"

class MovingEntity;

class MinerEntity : public MovingEntity {
public:
    ResourceType resource_type;
    MinerEntity(const mesh *, vec2, float, const float, const float, const JobType);
    void select();
    void deselect();

    std::string get_texture() override ;
    void set_texture(std::string src) override ;
};


#endif //C_AND_D_PROJECT_MINER_ENTITY_H
