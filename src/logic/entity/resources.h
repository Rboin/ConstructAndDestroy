#ifndef CONSTRUCT_AND_DESTROY_RESOURCES_H
#define CONSTRUCT_AND_DESTROY_RESOURCES_H

#include "entity/static/resource_type.h"
#include <sdl/sdl_render_object.h>
#include <sdl/ui/sdl_ui_render_text_object.h>
#include <vector>


class Resources {
private:
    float* _resources;
public:
    Resources();
    Resources(float gold, float wood, float stone, float iron);
    void add_resources(ResourceType ,float);
    float get_resources(ResourceType);
    virtual ~Resources();
};
#endif //CONSTRUCT_AND_DESTROY_RESOURCES_H
