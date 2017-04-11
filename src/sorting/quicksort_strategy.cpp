//
// Created by robin on 3/8/17.
//

#include "quicksort_strategy.h"
#include "vector.h"
#include "entity/base_entity.h"

std::vector<BaseEntity *> QuicksortStrategy::sort(BaseEntity *b, std::vector<BaseEntity *> entities) const {
    if (entities.size() > 1) {
        std::vector<BaseEntity *> smaller, same, greater;
        float chosen_distance = b->get_position().distance_squared(entities.at(entities.size() / 2)->get_position());

        for (unsigned int i = 0; i < entities.size(); i++) {
            BaseEntity *current = entities.at(i);
            float current_distance = b->get_position().distance_squared(current->get_position());
            if (b != current) {
                if (current_distance < chosen_distance)
                    smaller.push_back(current);
                else if (current_distance > chosen_distance)
                    greater.push_back(current);
                else
                    same.push_back(current);
            }
        }

        sort(b, smaller);
        sort(b, greater);

        std::vector<BaseEntity *> result;
        result.insert(result.end(), smaller.begin(), smaller.end());
        result.insert(result.end(), same.begin(), same.end());
        result.insert(result.end(), greater.begin(), greater.end());
        return result;
    }

    // Return empty vector if we don't need to sort and found ourselves at the first index
    if (entities.size() == 1 && entities.at(0) == b) {
        std::vector<BaseEntity *> empty;
        return empty;
    }
    return entities;
}

std::vector<BaseEntity *> QuicksortStrategy::sort(const vec2 &v, std::vector<BaseEntity *> entities) const {
    if (entities.size() > 1) {
        std::vector<BaseEntity *> smaller, same, greater;
        float chosen_distance = v.distance_squared(entities.at(entities.size() / 2)->get_position());

        for (unsigned int i = 0; i < entities.size(); i++) {
            BaseEntity *current = entities.at(i);
            float current_distance = v.distance_squared(current->get_position());
            if (current_distance < chosen_distance)
                smaller.push_back(current);
            else if (current_distance > chosen_distance)
                greater.push_back(current);
            else
                same.push_back(current);
        }

        sort(v, smaller);
        sort(v, greater);

        std::vector<BaseEntity *> result;
        result.insert(result.end(), smaller.begin(), smaller.end());
        result.insert(result.end(), same.begin(), same.end());
        result.insert(result.end(), greater.begin(), greater.end());
        return result;
    }
    return entities;
}
