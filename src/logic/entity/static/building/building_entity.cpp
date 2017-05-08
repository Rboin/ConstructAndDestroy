//
// Created by Stephan on 18-04-2017.
//

#include <entity/static/building/building_state/choosing_building_position.h>
#include "building_entity.h"
#include "building_manager.h"
#include "entity/state/state_machine.h"


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
}
