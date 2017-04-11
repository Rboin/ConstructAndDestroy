//
// Created by robin on 2/22/17.
//

#ifndef C_AND_D_PROJECT_MESH_H
#define C_AND_D_PROJECT_MESH_H

#include <vector.h>

struct s_mesh {
    const int size;
    vec2 *vectors;

    bool contains(const vec2 &v) const {
        int left, right;
        bool within_bounds = false;
        // Check whether the mouse vector lies within the bounds of the entity
        for (left = 0, right = size - 1; left < size; right = left++) {
            float dist_left_right_x = vectors[right].x - vectors[left].x;
            float dist_v_left_y = v.y - vectors[left].y;
            float dist_left_right_y = vectors[right].y - vectors[left].y;

            float dist_ratio = dist_left_right_x * (dist_v_left_y / dist_left_right_y) + vectors[left].x;

            bool in_between_y = (vectors[left].y > v.y) != (vectors[right].y > v.y);
            bool in_between_x = (v.x < dist_ratio);
            if (in_between_y && in_between_x) {
                within_bounds = !within_bounds;
            }
        }
        return within_bounds;
    }
};

#endif //C_AND_D_PROJECT_MESH_H
