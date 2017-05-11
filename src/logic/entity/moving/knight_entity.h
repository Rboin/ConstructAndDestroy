//
// Created by Stephan Schrijver on 9-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_KNIGHT_ENTITY_H
#define CONSTRUCT_AND_DESTROY_KNIGHT_ENTITY_H

#include "moving_entity.h"

class KnightEntity : public MovingEntity {
public:
    KnightEntity(const mesh *, vec2, float, const float, const float);
    void select();
    void deselect();

    std::string get_texture()override ;
    void set_texture(std::string src) override ;

};
#endif //CONSTRUCT_AND_DESTROY_KNIGHT_ENTITY_H
