#include "resources.h"


Resources::Resources() {
    _resources = new float[4]{0,0,0,0};
}

Resources::~Resources() {}

void Resources::add_resources(ResourceType rt, float amount) {
    switch (rt) {
        case TREE:
            _resources[1 << (int) WOOD] += amount;
            break;
        case IRONMINE:
            _resources[1 << (int) IRON] += amount;
            break;
    }
}

float Resources::get_resources(ResourceType rt) {
    return _resources[1 << (int) rt];
}
