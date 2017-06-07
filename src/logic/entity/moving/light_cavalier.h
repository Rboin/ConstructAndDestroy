//
// Created by Mark on 6-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_LIGHT_CAVALIER_H
#define CONSTRUCT_AND_DESTROY_LIGHT_CAVALIER_H

#include "moving_entity.h"

class LightCavalierEntity : public MovingEntity {
public:
    LightCavalierEntity(vec2, float);
    void select();
    void deselect();

    std::string get_texture() override;
    void set_texture(std::string src) override;
};


#endif //CONSTRUCT_AND_DESTROY_LIGHT_CAVALIER_H
