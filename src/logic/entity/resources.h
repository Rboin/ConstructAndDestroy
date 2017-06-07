#ifndef CONSTRUCT_AND_DESTROY_RESOURCES_H
#define CONSTRUCT_AND_DESTROY_RESOURCES_H

#include "entity/static/resource_type.h"
#include <string>


class Resources {
private:
    float *_resources;
public:
    Resources();

    Resources(float gold, float wood, float stone, float iron);

    void add_resources(ResourceType, float);

    float get_resources(ResourceType);

    std::string get_texture_by_type(ResourceType);

    virtual ~Resources();

    bool check_if_sufficient_resources(Resources *);

    void subtract_resources(Resources *);
};

#endif //CONSTRUCT_AND_DESTROY_RESOURCES_H
