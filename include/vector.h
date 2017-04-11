//
// Created by robin on 2/21/17.
//
// This file contains the definition for the matrix and vector structures.
//

#ifndef C_AND_D_PROJECT_VECTOR_H
#define C_AND_D_PROJECT_VECTOR_H

#include "types.h"

/**
 * The Vector2D structure.
 */
struct s_vec2 {
    float x, y, w;

    s_vec2();

    s_vec2(float, float);

    s_vec2(float, float, float);

    vec2 clone() const;

    vec2 truncate(float) const;

    float length() const;

    float length_sqrt() const;

    float distance(const vec2 &) const;

    float distance_squared(const vec2 &) const;

    vec2 normalize() const;

    bool operator==(const vec2 &) const;

    bool operator!=(const vec2 &) const;

    vec2 operator+(const vec2 &) const;

    vec2 operator+=(const vec2 &);

    vec2 operator-(const vec2 &) const;

    vec2 operator*(mat2) const;

    vec2 operator*(float) const;

    vec2 operator*=(float);

    vec2 operator/(float) const;

};

void wrap_around(vec2 &);

#endif //C_AND_D_PROJECT_VECTOR_H
