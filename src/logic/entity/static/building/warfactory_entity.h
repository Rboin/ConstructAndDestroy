//
// Created by Mark on 6-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_BARRACKS_H
#define CONSTRUCT_AND_DESTROY_BARRACKS_H

#include "building_entity.h"

class WarfactoryEntity : public BuildingEntity {
public:
    WarfactoryEntity(vec2, float);
    WarfactoryEntity(float);
    void set_transparent_or_border(bool, bool = true);

    void select() override ;
    void deselect() override;
};



#endif //CONSTRUCT_AND_DESTROY_BARRACKS_H
