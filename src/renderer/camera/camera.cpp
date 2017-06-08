//
// Created by robin on 5/29/17.
//

#include <iostream>
#include "camera.h"
#include "settings.h"

Camera *Camera::_instance = nullptr;

Camera::Camera(vec2 pos, vec2 size) {
    _position = pos;
    _translation = mat2::translate(pos);
    _rotation = mat2::rotate(0.0f);
    _scale = mat2::scale(1.0f);

    _movement_buffer = vec2();

    _world_rectangle[0] = pos;
    _world_rectangle[1] = {pos.x + size.x, pos.y};
    _world_rectangle[2] = pos + size;
    _world_rectangle[3] = {pos.x, pos.y + size.y};
}

Camera::~Camera() {
    _instance = nullptr;
}

Camera *Camera::get_instance() {
    if(!_instance) {
        _instance = new Camera(camera_initial_position, window_size);
    }
    return _instance;
}

void Camera::update(float delta) {
    vec2 delta_move = _movement_buffer * delta;
    vec2 tmp_position = _position + delta_move;
    mat2 tmp_translation = mat2::translate(tmp_position);

    _movement_buffer = vec2();

    vec2 top_left = (_world_rectangle[0] * tmp_translation),
        bottom_right = (_world_rectangle[2] * tmp_translation) * _scale.inverse();
    if(top_left.x < 0) {
        tmp_position.x = 0;
    }
    if(top_left.y < 0) {
        tmp_position.y = 0;
    }
    if(bottom_right.x > world_size.x) {
        float new_x = world_size.x - (bottom_right.x - top_left.x);
        tmp_position.x = new_x - 1;
    }
    if(bottom_right.y > world_size.y) {
        float new_y = world_size.y - (bottom_right.y - top_left.y);
        tmp_position.y = new_y - 1;
    }
    _position = tmp_position;
    update_all();
}

mat2 Camera::get_world_translation() {
    return mat2::translate(_position * -1.0f);
}

void Camera::move(const vec2 &v) {
    _movement_buffer += v;
}

void Camera::zoom(float f) {
    camera_zoom = std::max(camera_min_zoom, std::min(camera_max_zoom, camera_zoom + f));
}

void Camera::update_world_buffer() {
    for (int i = 0; i < sizeof(_world_rectangle) / sizeof(vec2); i++) {
        if(i == 0) {
            _world_rectangle_buffer[i] = _world_rectangle[i] * _translation;
        } else {
            _world_rectangle_buffer[i] = (_world_rectangle[i] * _translation) * _scale.inverse();
        }
    }
}

void Camera::update_translation() {
    _translation = mat2::translate(_position);
}

void Camera::update_rotation() {
    // TODO: Move rotation to variable.
    _rotation = mat2::rotate(0.0f);
}

void Camera::update_scale() {
    _scale = mat2::scale(camera_zoom);
}

void Camera::update_model() {
    _model = _translation * _rotation * _scale;
}

const mat2 &Camera::get_world_model() {
    return _world_model;
}

mat2 Camera::get_inversed_scale() {
    return _scale.inverse();
}

mat2 Camera::get_translation() {
    return _translation;
}

void Camera::update_world_model() {
    _world_model = get_world_translation() * _rotation * _scale;
}

const mat2 &Camera::get_model() {
    return _model;
}

void Camera::update_all() {
    update_translation();
    update_rotation();
    update_scale();
    update_model();
    update_world_model();
    update_world_buffer();
}

void Camera::update_size(const vec2 &v) {
    camera_zoom = 1.0f;
    _world_rectangle[1] = {_world_rectangle[0].x + v.x, _world_rectangle[0].y};
    _world_rectangle[2] = _world_rectangle[0] + v;
    _world_rectangle[3] = {_world_rectangle[0].x, _world_rectangle[0].y + v.y};
    update_all();
}



