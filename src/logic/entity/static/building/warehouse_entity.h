//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_WAREHOUSE_ENTITY_H
#define C_AND_D_PROJECT_WAREHOUSE_ENTITY_H

#include "building_entity.h"

class WarehouseEntity : public BuildingEntity {
public:
    WarehouseEntity(const mesh *, vec2, float);
    WarehouseEntity(const mesh *, float);
    void set_transparent_or_border(bool, bool = true);
};


#endif //C_AND_D_PROJECT_WAREHOUSE_ENTITY_H
