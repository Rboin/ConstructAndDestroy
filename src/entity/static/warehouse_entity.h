//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_WAREHOUSE_ENTITY_H
#define C_AND_D_PROJECT_WAREHOUSE_ENTITY_H

#include "resource_entity.h"

class ResourceEntity;

class WarehouseEntity : public ResourceEntity {
public:
    WarehouseEntity(const mesh *, vec2, float);
};


#endif //C_AND_D_PROJECT_WAREHOUSE_ENTITY_H
