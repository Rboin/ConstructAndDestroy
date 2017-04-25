//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_RENDERING_OBJECT_H
#define CONSTRUCT_AND_DESTROY_RENDERING_OBJECT_H

#include "types.h"
#include "vector.h"

//struct color {
//    uint8_t red, green, blue;
//};

template<typename T>
class Renderer;

/**
 *
 * @tparam T = Type of renderer.
 * @tparam D = RenderObject data type.
 * @tparam R = Result of render method.
 */
template<typename T, typename D, typename R>
class RenderObject {
protected:
    vec2 _position, _size;
    D _data;
    R *_result;
public:

    explicit RenderObject(vec2 position, vec2 size, D data) {
        _position = position;
        _size = size;
        _data = data;
        _result = nullptr;
    }

    const vec2 *get_position() {
        return &_position;
    }

    const vec2 *get_size() {
        return &_size;
    }

    D *get_data() {
        return &_data;
    }

    /**
     * Check whether the given point is within our bounds.
     * @param v
     * @return
     */
    bool contains(vec2 v) {
        vec2 B = {_position.x + _size.x, _position.y},
                C = {_position.x + _size.x, _position.y + _size.y};
        vec2 AB = B - _position,
                AP = v - _position,
                BC = C - B,
                BP = v - B;
        bool within_horizontal_bounds = AB.dot(AB) > AB.dot(AP) && AB.dot(AP) > 0,
                within_vertical_bounds = BC.dot(BC) > BC.dot(BP) && BC.dot(BP) > 0;
        return within_horizontal_bounds && within_vertical_bounds;
    }

    virtual R *render(Renderer<T> *) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_RENDERING_OBJECT_H
