//
// Created by Stephan Schrijver on 3-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_BUILDING_FACTORY_H
#define CONSTRUCT_AND_DESTROY_BUILDING_FACTORY_H

#include "types.h"
#include <string>

class BuildingEntity;

class BuildingFactory {
private:
    static vec2* default_shape;
    static mesh *base;

public:
    static BuildingEntity *create(std::string);

};

#endif //CONSTRUCT_AND_DESTROY_BUILDING_FACTORY_H
