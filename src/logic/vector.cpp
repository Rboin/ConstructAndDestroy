//
// Created by robin on 2/21/17.
//
#include <cmath>
#include <limits>
#include <matrix.h>
#include "vector.h"

s_vec2::s_vec2() : vec2(0, 0, 1) {}

s_vec2::s_vec2(float x, float y) : vec2(x, y, 1) {}

s_vec2::s_vec2(float x, float y, float w) : x(x), y(y), w(w) {}

bool s_vec2::operator==(const vec2 &v) const {
    return &v == this || (x == v.x && y == v.y && w == v.w);
}

bool s_vec2::operator!=(const vec2 &v) const {
    return !(*this == v);
}

vec2 s_vec2::operator+(const vec2 &v) const {
    return {x + v.x, y + v.y, w};
}

vec2 s_vec2::operator+=(const vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
}

vec2 s_vec2::operator-(const vec2 &v) const {
    return {x - v.x, y - v.y, w};
}

vec2 s_vec2::operator-=(const vec2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

vec2 s_vec2::operator*(mat2 m) const {
    return m * (*this);
}

vec2 s_vec2::operator*=(float f) {
    x *= f;
    y *= f;
    return *this;
}

vec2 s_vec2::operator*(float f) const {
    return {x * f, y * f, w};
}

vec2 s_vec2::operator/(float f) const {
    return {x / f, y / f, w};
}

vec2 s_vec2::clone() const {
    return {x, y, w};
}

//Truncate the vector so the length does not exceed speed
vec2 s_vec2::truncate(float f) const {
    if (length() > f)
        return normalize() * f;

    return *this;
};

float s_vec2::length() const {
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

//Return the squared length of a vector
float s_vec2::length_sqrt() const {
    return (x * x + y * y);
};

float s_vec2::distance(const vec2 &v) const {
    vec2 distance = {(x - v.x), (y - v.y)};
    return distance.length();
}

float s_vec2::distance_squared(const vec2 &v) const {
    vec2 distance = {(x - v.x), (y - v.y)};
    return distance.length_sqrt();
}

vec2 s_vec2::normalize() const {
    float l = length();
    if (!l)
        return *this;
    return *this / l;
}

float s_vec2::dot(const vec2 &v) const {
    return (x * v.x) + (y * v.y);
}

vec2 operator-(const vec2 &v) {
    return {0 - v.x, 0 - v.y, v.w};
}
