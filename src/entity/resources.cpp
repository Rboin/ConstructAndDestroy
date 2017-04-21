#include "resources.h"

Resources::Resources() {
    gold = 0.0f;
    wood = 0.0f;
    stone = 0.0f;
    iron = 0.0f;
}

Resources::Resources(float gold, float wood, float stone, float iron) {
    this->gold = gold;
    this->wood = wood;
    this->stone = stone;
    this->iron = iron;
}

Resources::~Resources() {}

void Resources::add_resources(ResourceType rt, float amount) {
    switch (rt) {
        case TREE:
            wood += amount;
            break;
        case IRONMINE:
            iron += amount;
            break;
    }

}
