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

/**
 *
 * @tparam T = Type of renderer.
 * @tparam D = RenderObject data type.
 * @tparam R = Result of render method.
 */
template<typename T, typename D, typename R>
class RenderObject {
protected:
    vec2 _points[4];
    vec2 _position, _size;
    D *_data;
    R *_result;

    void update_points() {
        _points[0] = _position;
        _points[1] = vec2(_position.x + _size.x, _position.y);
        _points[2] = _position + _size;
        _points[3] = vec2(_position.x, _position.y + _size.y);
    }
public:

    explicit RenderObject(vec2 position, vec2 size, D *data) {
        _position = position;
        _size = size;
        _data = data;
        _result = nullptr;

        update_points();
    }

    virtual ~RenderObject() {}

    virtual void clear_data() = 0;

    const vec2 *get_position() {
        return &_position;
    }

    virtual void set_position(float x, float y) {
        _position.x = x;
        _position.y = y;
        update_points();
    }

    const vec2 *get_size() {
        return &_size;
    }

    void set_size(const vec2 &v) {
        _size.x = v.x;
        _size.y = v.y;
        update_points();
    }

    virtual D *get_data() {
        return _data;
    }

    void set_data(D *d) {
        delete _data;
        _data = d;
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

    virtual void render(T *, const mat2 &) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_RENDERING_OBJECT_H
