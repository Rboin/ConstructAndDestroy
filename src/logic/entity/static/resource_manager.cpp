//
// Created by Sander on 20-3-2017.
//

#include "entity/moving/moving_entity.h"
#include "resource_manager.h"

ResourceManager *ResourceManager::instance = nullptr;

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
    if (resources.size() > 0) {
        for (int i = 0; i < resources.size(); i++) {
            delete resources.at(i);
        }
    }
}

ResourceManager *ResourceManager::get_instance() {
    if (!instance)
        instance = new ResourceManager();
    return instance;
}

void ResourceManager::add_resource(ResourceEntity *re) {
    resources.emplace_back(re);
}

std::vector<ResourceEntity *> ResourceManager::get_resources() {
    return resources;
}

vec2 ResourceManager::get_closest_resource(vec2 pos, ResourceType rt) {
    float distance = -1;
    vec2 closest;
    for (int i = 0; i < resources.size(); i++) {
        if(resources.at(i)->is_depleted()){
            continue;
        }
        if (distance == -1 && rt == resources.at(i)->get_resource_type() ||
            pos.distance(resources.at(i)->get_position()) < distance && rt == resources.at(i)->get_resource_type()) {
            distance = pos.distance(resources.at(i)->get_position());
            closest = resources.at(i)->get_position();
        }
    }
    return closest;
}

vec2 ResourceManager::get_closest_resource(vec2 pos) {
    float distance = -1;
    vec2 closest;
    for (int i = 0; i < resources.size(); i++) {
        if (distance == -1 || pos.distance(resources.at(i)->get_position()) < distance) {
            distance = pos.distance(resources.at(i)->get_position());
            closest = resources.at(i)->get_position();
        }
    }
    return closest;
}

ResourceType ResourceManager::get_resource_type(JobType jt) {
    ResourceType rt;
    if (jt == WOODCUTTER) { rt = WOOD; }
    if (jt == IRONMINER) { rt = IRON; }
    if (jt == GOLDMINER) {rt = GOLD;}
    if (jt == STONEMINER) {rt = STONE;}
    return rt;
}

ResourceEntity *ResourceManager::get_resource(vec2 *pos) {
    for (int i = 0; i < resources.size(); i++) {
        if (resources.at(i)->get_position() == *pos) {
            return resources.at(i);
        }
    }
}

void ResourceManager::replenish_resources(float d_t) {
    for(int i = 0; i < resources.size(); i++){
        resources.at(i)->replenish_resource(d_t);
    }
}
