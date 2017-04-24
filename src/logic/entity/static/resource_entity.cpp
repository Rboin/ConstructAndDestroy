//
// Created by Sander on 20-3-2017.
//

#include "resource_entity.h"
#include "resource_manager.h"

ResourceEntity::ResourceEntity(const mesh *base, vec2 position, float mass, ResourceType rt, TextureTypes resourcetype)
        : StaticEntity(base,
                       position,
                       mass, resourcetype) {
    resource_type = rt;
    units = 250.f;

    //add resource to resource manager
    ResourceManager *rm = ResourceManager::get_instance();
    rm->add_resource(this);
}

ResourceType ResourceEntity::get_resource_type() {
    return resource_type;
}

int ResourceEntity::get_units() {
    return units;
}

float ResourceEntity::gather() {
    units -= 0.001;
    return 0.001;
}

