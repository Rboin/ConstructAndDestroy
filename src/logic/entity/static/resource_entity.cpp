//
// Created by Sander on 20-3-2017.
//

#include <sdl/image/sdl_image_render_object.h>
#include "resource_entity.h"
#include "resource_manager.h"
#include <string>

ResourceEntity::ResourceEntity(const mesh *base, vec2 position, float mass, ResourceType rt)
        : StaticEntity(base,
                       position,
                       mass) {
    resource_type = rt;
    _units = 50.f;
    _depleted = false;
    _max_units = 250.f;
    _replenish_rate = 0.0001f;
    //add resource to resource manager
    ResourceManager *rm = ResourceManager::get_instance();
    rm->add_resource(this);
}

ResourceType ResourceEntity::get_resource_type() {
    return resource_type;
}

int ResourceEntity::get_units() {
    return (int)_units;
}

float ResourceEntity::gather() {
    _units -= 0.001;
    if (_units < 10) {
        _depleted = true;
        update_texture();
    }
    return 0.001;
}

void ResourceEntity::replenish_resource() {
    if (_units <= _max_units) {
        _units += _replenish_rate;
    }
    if (_units >= 100) {
        _depleted = false;
        update_texture();
    }
}

bool ResourceEntity::is_depleted() {
    return _depleted;
}

void ResourceEntity::update_texture() {
    sdl_image_data *data = (sdl_image_data *) this->get_representation()->get_data();
    if (_current_texture != _texture && !_depleted) {
        _current_texture = _texture;
    } else if (_current_texture != _depleted_texture && _depleted) {
        _current_texture = _depleted_texture;
    }
    data->type = _current_texture;
    this->get_representation()->clear_data();
    // TODO reset texture
}

void ResourceEntity::set_textures(TextureTypes normal, TextureTypes depleted) {
    _texture = normal;
    _depleted_texture = depleted;
}
