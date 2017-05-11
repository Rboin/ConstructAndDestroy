//
// Created by Sander on 4-4-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "warehouse_entity.h"

WarehouseEntity::WarehouseEntity(const mesh *base, vec2 position, float mass) : BuildingEntity(
        base, position, mass, WAREHOUSE, WAREHOUSETEXTURE) {
}
WarehouseEntity::WarehouseEntity(const mesh *base, float mass) : BuildingEntity(
        base, mass, WAREHOUSE, WAREHOUSETEXTURE) {
}

void WarehouseEntity::set_transparent_or_border(bool transparent, bool border) {
    // NOT IMPLEMENTED YET!
}