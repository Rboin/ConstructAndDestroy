//
// Created by Sander on 20-3-2017.
//

#ifndef C_AND_D_PROJECT_RESOURCE_ENTITY_H
#define C_AND_D_PROJECT_RESOURCE_ENTITY_H


#include "static_entity.h"
#include "resource_type.h"

class ResourceEntity : public StaticEntity {
private:
    ResourceType resource_type;
    float units;
public:
    ResourceEntity(const mesh*,vec2,float, ResourceType);

    ResourceType get_resource_type();

    int get_units();

    float gather();
};


#endif //C_AND_D_PROJECT_RESOURCE_ENTITY_H
