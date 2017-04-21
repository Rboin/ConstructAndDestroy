//
// Created by Sander on 20-3-2017.
//

#ifndef C_AND_D_PROJECT_RESOURCE_MANAGER_H
#define C_AND_D_PROJECT_RESOURCE_MANAGER_H


#include "entity/static/resource_entity.h"
#include "entity/goal/moving_entity_goal/job_type.h"

class ResourceManager {
private:
    ResourceManager();

    static ResourceManager *instance;

    std::vector<ResourceEntity *> resources;
public:
    ~ResourceManager();

    static ResourceManager *get_instance();

    void add_resource(ResourceEntity*);

    std::vector<ResourceEntity *> get_resources();

    vec2 get_closest_resource(vec2, ResourceType);

    vec2 get_closest_resource(vec2);

    ResourceType get_resource_type(JobType);

    /*!
     * @return returns the resource entity that matches the position
     */
    ResourceEntity* get_resource(vec2*);
};


#endif //C_AND_D_PROJECT_RESOURCE_MANAGER_H
