
#include "resources.h"

Resources::Resources() {
    _resources = new float[4]{0, 0, 0, 0};
}

Resources::Resources(float gold, float wood, float stone, float iron) {
    _resources = new float[4]{gold, wood, stone, iron};
}

Resources::~Resources() {
    delete[] _resources;
}

void Resources::add_resources(ResourceType rt, float amount) {
    _resources[(int) rt] += amount;
}

float Resources::get_resources(ResourceType rt) {
    return _resources[(int) rt];
}

void Resources::subtract_resources(Resources *r) {
    for (int i = 0; i < 4; i++) {
        _resources[i] -= r->_resources[i];
    }
}

bool Resources::check_if_sufficient_resources(Resources *r) {
    for (int i = 0; i < 4; i++) {
        if (_resources[i] < r->_resources[i]) {
            return false;
        }
    }
    return true;
}

std::string Resources::get_texture_by_type(ResourceType resource_type) {
    std::string result = "";
    switch(resource_type){
        case STONE:
            result = "stone.png";
            break;
        case GOLD:
            result = "gold.png";
            break;
        case WOOD:
            result = "log.png";
            break;
    }

    return result;
}

void Resources::reset() {
    for (int i = 0; i < 4; i++) {
        _resources[i] = 50;
    }
}
