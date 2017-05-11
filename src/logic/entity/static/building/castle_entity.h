//
// Created by Stephan on 18-4-2017.
//

#ifndef C_AND_D_PROJECT_CASTLE_ENTITY_H
#define C_AND_D_PROJECT_CASTLE_ENTITY_H

#include "building_entity.h"

class CastleEntity : public BuildingEntity {
public:
    CastleEntity(const mesh *, vec2, float);
    CastleEntity(const mesh *, float);
    void set_transparent_or_border(bool, bool = false);
};

#endif //C_AND_D_PROJECT_CASTLE_ENTITY_H
