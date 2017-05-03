#ifndef CONSTRUCT_AND_DESTROY_RESOURCES_H
#define CONSTRUCT_AND_DESTROY_RESOURCES_H

#include "entity/static/resource_type.h"

class Resources {
public:
    float gold;
    float wood;
    float stone;
    float iron;

    Resources();
    Resources(float gold, float wood, float stone, float iron);
    void add_resources(ResourceType ,float);
    virtual ~Resources();

};
#endif //CONSTRUCT_AND_DESTROY_RESOURCES_H
