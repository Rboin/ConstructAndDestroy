//
// Created by robin on 3/8/17.
//

#ifndef C_AND_D_PROJECT_SORTSTRATEGY_H
#define C_AND_D_PROJECT_SORTSTRATEGY_H

#include <vector>
#include "types.h"

template<class T>
class SortStrategy {
public:
    virtual std::vector<T *> sort(const vec2 &, std::vector<T *>) const = 0;
    virtual std::vector<T *> sort(T *, std::vector<T *>) const = 0;
};


#endif //C_AND_D_PROJECT_SORTSTRATEGY_H
