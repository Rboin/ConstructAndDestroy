//
// Created by Sander on 1-3-2017.
//

#ifndef C_AND_D_PROJECT_STATIC_ENTITY_H
#define C_AND_D_PROJECT_STATIC_ENTITY_H


#include "base_entity.h"

class StaticEntity : public BaseEntity {
public:
    StaticEntity(const mesh *, vec2, float, TextureTypes);
};


#endif //C_AND_D_PROJECT_STATIC_ENTITY_H
