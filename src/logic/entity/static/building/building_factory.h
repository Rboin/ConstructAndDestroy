//
// Created by Stephan Schrijver on 3-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_BUILDING_FACTORY_H
#define CONSTRUCT_AND_DESTROY_BUILDING_FACTORY_H

#include "types.h"
#include "building_type.h"
#include <string>

class BuildingEntity;

class BuildingFactory {
public:
    static BuildingEntity *create(BuildingType);

};

#endif //CONSTRUCT_AND_DESTROY_BUILDING_FACTORY_H
