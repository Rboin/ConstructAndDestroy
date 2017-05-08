//
// Created by Sander on 20-3-2017.
//

#ifndef C_AND_D_PROJECT_RESOURCE_MANAGER_H
#define C_AND_D_PROJECT_RESOURCE_MANAGER_H


#include "resource_entity.h"
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

    /*!
     * @return the closest resource that isn't depleted and matches the given resource type
     */
    vec2 get_closest_resource(vec2, ResourceType);

    /*!
     * @return the closest resource
     */
    vec2 get_closest_resource(vec2);
    
    ResourceType get_resource_type(JobType);

    /*!
     * @return returns the resource entity that matches the position
     */
    ResourceEntity* get_resource(vec2*);

    /*!
     * This function calls the replenish_resource of all the resource entities
     */
    void replenish_resources(float d_t);
};


#endif //C_AND_D_PROJECT_RESOURCE_MANAGER_H
