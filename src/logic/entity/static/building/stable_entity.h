//
// Created by Mark on 1-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_STABLE_ENTITY_H
#define CONSTRUCT_AND_DESTROY_STABLE_ENTITY_H

#include "building_entity.h"


class StableEntity : public BuildingEntity {
public:
    StableEntity(vec2, float);
    StableEntity(float);
    void set_transparent_or_border(bool, bool = true);

    void select() override ;
    void deselect() override;
};

#endif //CONSTRUCT_AND_DESTROY_STABLE_ENTITY_H
