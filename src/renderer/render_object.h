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

    const D *get_color() {
        return &_data;
    }

    virtual R *render(Renderer<T> *) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_RENDERING_OBJECT_H
