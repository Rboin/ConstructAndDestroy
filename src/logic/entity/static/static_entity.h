//
// Created by Sander on 1-3-2017.
//

#ifndef C_AND_D_PROJECT_STATIC_ENTITY_H
#define C_AND_D_PROJECT_STATIC_ENTITY_H


#include "entity/base_entity.h"

class StaticEntity : public BaseEntity {
public:
    StaticEntity(vec2, float);
    StaticEntity(float);
    void set_position(float, float, bool);
};


#endif //C_AND_D_PROJECT_STATIC_ENTITY_H
