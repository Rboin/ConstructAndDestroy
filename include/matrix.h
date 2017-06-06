//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_MATRIX_H
#define C_AND_D_PROJECT_MATRIX_H

#include "types.h"

/**
 * The Matrix structure.
 */
struct s_mat2 {
    float x1, x2, x3,
            y1, y2, y3,
            w1, w2, w3;

    // Constructors
    s_mat2();

    s_mat2(vec2);

    s_mat2(vec2, float);

    s_mat2(float, float, float);

    s_mat2(float x1, float x2, float x3,
           float y1, float y2, float y3,
           float w1, float w2, float w3);

    static mat2 scale(float);

    static mat2 scale(float, float);

    static mat2 rotate(float);

    static mat2 translate(float, float);

    static mat2 translate(vec2);

    mat2 inverse();

    vec2 operator*(vec2);

    mat2 operator*(mat2);

    mat2 operator*(float);
};

#endif //C_AND_D_PROJECT_MATRIX_H
