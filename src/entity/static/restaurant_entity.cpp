//
// Created by Sander on 4-4-2017.
//

#include "restaurant_entity.h"


RestaurantEntity::RestaurantEntity(const mesh *base, vec2 position, float mass) : ResourceEntity(
        base, position, mass, RESTAURANT, RESTAURANTTEXTURE) {
}