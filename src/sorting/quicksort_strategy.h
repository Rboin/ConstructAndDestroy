//
// Created by robin on 3/8/17.
//

#ifndef C_AND_D_PROJECT_QUICKSORT_STRATEGY_H
#define C_AND_D_PROJECT_QUICKSORT_STRATEGY_H

#include "sort_strategy.h"

class BaseEntity;

class QuicksortStrategy : public SortStrategy<BaseEntity> {
public:
    std::vector<BaseEntity *> sort(const vec2 &, std::vector<BaseEntity *> vector) const override;

    std::vector<BaseEntity *> sort(BaseEntity *, std::vector<BaseEntity *>) const override;
};


#endif //C_AND_D_PROJECT_QUICKSORT_STRATEGY_H
