//
// Created by Sander on 20-3-2017.
//

#include "entity/moving/moving_entity.h"
#include "resource_manager.h"

ResourceManager *ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
    if (_resources.size() > 0) {
        for (int i = 0; i < _resources.size(); i++) {
            delete _resources.at(i);
        }
    }
    _resources.clear();
    _instance = nullptr;
}

ResourceManager *ResourceManager::get_instance() {
    if (!_instance)
        _instance = new ResourceManager();
    return _instance;
}

void ResourceManager::add_resource(ResourceEntity *re) {
    _resources.emplace_back(re);
}

std::vector<ResourceEntity *> ResourceManager::get_resources() {
    return _resources;
}

vec2 ResourceManager::get_closest_resource(vec2 pos, ResourceType rt) {
    float distance = -1;
    vec2 closest;
    for (int i = 0; i < _resources.size(); i++) {
        if(_resources.at(i)->is_depleted()){
            continue;
        }
        if (distance == -1 && rt == _resources.at(i)->get_resource_type() ||
            pos.distance(_resources.at(i)->get_position()) < distance && rt == _resources.at(i)->get_resource_type()) {
            distance = pos.distance(_resources.at(i)->get_position());
            closest = _resources.at(i)->get_position();
        }
    }
    return closest;
}

vec2 ResourceManager::get_closest_resource(vec2 pos) {
    float distance = -1;
    vec2 closest;
    for (int i = 0; i < _resources.size(); i++) {
        if (distance == -1 || pos.distance(_resources.at(i)->get_position()) < distance) {
            distance = pos.distance(_resources.at(i)->get_position());
            closest = _resources.at(i)->get_position();
        }
    }
    return closest;
}

ResourceType ResourceManager::get_resource_type(JobType jt) {
    ResourceType rt;
    if (jt == WOODCUTTER) { rt = WOOD; }
    if (jt == IRONMINER) { rt = IRON; }
    if (jt == GMINER) {rt = GOLD;}
    if (jt == SMINER) {rt = STONE;}
    return rt;
}

ResourceEntity *ResourceManager::get_resource(vec2 *pos) {
    for (int i = 0; i < _resources.size(); i++) {
        if (_resources.at(i)->get_position() == *pos) {
            return _resources.at(i);
        }
    }
}

void ResourceManager::replenish_resources(float d_t) {
    for(int i = 0; i < _resources.size(); i++){
        _resources.at(i)->replenish_resource(d_t);
    }
}
