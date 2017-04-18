//
// Created by robin on 3/8/17.
//

#ifndef C_AND_D_PROJECT_NEIGHBOURHOOD_MANAGER_H
#define C_AND_D_PROJECT_NEIGHBOURHOOD_MANAGER_H

#include <vector>
#include "types.h"
#include "sorting/sort_strategy.h"

class BSPTree;

class BaseEntity;

struct bsp_node;

class NeighbourhoodManager {
private:
    SortStrategy<BaseEntity> *sorter;

    BSPTree *tree;

    NeighbourhoodManager();

    static NeighbourhoodManager *instance;

public:
    ~NeighbourhoodManager();

    void setup(vec2, vec2);

    /**
     * Get the entities in the same neighbourhood, sorted by distance.
     * @return
     */
    std::vector<BaseEntity *> get_neighbours(BaseEntity *) const;

    BaseEntity *get_closest_to(vec2);
    /**
     * Updates the partitioning tree.
     */
    void update(BaseEntity *);

    void insert(BaseEntity *);

    static NeighbourhoodManager *get_instance();
};


#endif //C_AND_D_PROJECT_NEIGHBOURHOOD_MANAGER_H
