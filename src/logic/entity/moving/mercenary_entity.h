//
// Created by Mark on 6-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_MERCENARY_H
#define CONSTRUCT_AND_DESTROY_MERCENARY_H

#include "moving_entity.h"

class MercenaryEntity : public MovingEntity {
public:
    MercenaryEntity(vec2, float, const float, const float);
    void select();
    void deselect();

    std::string get_texture() override;
    void set_texture(std::string src) override;
};

#endif //CONSTRUCT_AND_DESTROY_MERCENARY_H
