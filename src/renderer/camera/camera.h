//
// Created by robin on 5/29/17.
//

#ifndef CONSTRUCT_AND_DESTROY_CAMERA_H
#define CONSTRUCT_AND_DESTROY_CAMERA_H

#include "types.h"
#include "vector.h"
#include "matrix.h"

class Camera {
private:
    mat2 _translation, _rotation, _scale, _model, _world_model;
    vec2 _movement_buffer, _position, _world_rectangle[4], _world_rectangle_buffer[4];

    static Camera *_instance;

    Camera(vec2, vec2);

    void update_world_buffer();

    void update_translation();

    void update_rotation();

    void update_scale();

    void update_model();

    void update_world_model();

    void update_all();

public:
    ~Camera();

    static Camera *get_instance();

    void update(float);

    mat2 get_world_translation();

    mat2 get_translation();

    mat2 get_inversed_scale();

    const mat2 &get_model();

    const mat2 &get_world_model();

    void move(const vec2 &v);

    void zoom(float);

    void update_size(const vec2 &);
};

#endif //CONSTRUCT_AND_DESTROY_CAMERA_H
