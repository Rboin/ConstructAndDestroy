//
// Created by Stephan on 18-04-2017.
//

#include "building_entity.h"
#include "building_manager.h"
#include "entity/resources.h"

BuildingEntity::BuildingEntity(const mesh *base, vec2 position, float mass, BuildingType bt, TextureTypes texture_types)
        : StaticEntity(base,
                       position,
                       mass) {
    building_type = bt;
}

BuildingEntity::BuildingEntity(const mesh *base, float mass, BuildingType bt, TextureTypes texture_types)
        : StaticEntity(base,
                       mass) {
    building_type = bt;
    costs = new Resources(0, 100, 100, 0);
}

Resources *BuildingEntity::get_costs() {
    return costs;
}

BuildingType BuildingEntity::get_building_type() {
    return building_type;
}
