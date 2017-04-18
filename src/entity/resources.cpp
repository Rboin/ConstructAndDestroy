#include "resources.h"

Resources::Resources() {
    gold = 0.0f;
    wood = 0.0f;
    stone = 0.0f;
}

Resources::Resources(float gold, float wood, float stone) {
    this->gold = gold;
    this->wood = wood;
    this->stone = stone;
}

Resources::~Resources() {}