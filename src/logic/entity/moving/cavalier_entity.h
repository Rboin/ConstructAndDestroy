//
// Created by Mark on 1-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_CAVALIER_ENTITY_H
#define CONSTRUCT_AND_DESTROY_CAVALIER_ENTITY_H

#include "moving_entity.h"

class CavalierEntity : public MovingEntity {
public:
    CavalierEntity(vec2, float);
    void select();
    void deselect();

    std::string get_texture() override;
    void set_texture(std::string src) override;
};

#endif //CONSTRUCT_AND_DESTROY_CAVALIER_ENTITY_H
