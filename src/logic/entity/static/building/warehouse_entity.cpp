//
// Created by Sander on 4-4-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "warehouse_entity.h"

WarehouseEntity::WarehouseEntity(vec2 position, float mass) : BuildingEntity(
        position, mass, WAREHOUSE, WAREHOUSETEXTURE) {
}
WarehouseEntity::WarehouseEntity(float mass) : BuildingEntity(
        mass, WAREHOUSE, WAREHOUSETEXTURE) {
}

void WarehouseEntity::set_transparent_or_border(bool transparent, bool border) {
    // NOT IMPLEMENTED YET!
}

void WarehouseEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_warehouse.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

void WarehouseEntity::deselect() {
    sdl_image_data* entity_data =  new sdl_image_data{"warehouse.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}