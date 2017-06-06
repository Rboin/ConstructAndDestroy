//
// Created by robin on 5/31/17.
//

#include <SDL_mouse.h>
#include "camera_manager.h"
#include "settings.h"
#include "camera.h"
#include "world/world.h"

template void
CameraManager::render<World, SDLRenderer, mat2>(SDLRenderer *, World *, void (World::*)(SDLRenderer *, const mat2 &));

CameraManager *CameraManager::_instance = nullptr;

CameraManager::CameraManager(Camera *c) : _camera(c) {
}

CameraManager::~CameraManager() {
    delete _camera;
}

CameraManager *CameraManager::get_instance() {
    if(!_instance) {
        _instance = new CameraManager(Camera::get_instance());
    }
    return _instance;
}

void CameraManager::add_to_position(const vec2 &v) {
    _camera->move(v);
}

void CameraManager::zoom(float f) {
    _camera->zoom(f);
}

template<typename W, typename T, typename M>
void CameraManager::render(T *t, W *w, void (W::*f)(T *, const M &)) {
    (w->*f)(t, _camera->get_world_model());
}

void CameraManager::update(float d_t) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    float top = camera_scroll_margin, right = window_size.x - camera_scroll_margin,
        bottom = window_size.y - camera_scroll_margin, left = camera_scroll_margin;
    vec2 camera_move = {0, 0};
    if(y <= top && y >= 1 ) {
        camera_move += {0.0f, -camera_movement_speed};
    }
    if(x >= right && x <= window_size.x) {
        camera_move += {camera_movement_speed, 0.0f};
    }
    if(y >= bottom && y <= window_size.y) {
        camera_move += {0.0f, camera_movement_speed};
    }
    if(x <= left && x >= 1) {
        camera_move += {-camera_movement_speed, 0.0f};
    }
    if(camera_move.distance({0, 0}) > 0.0f) {
        add_to_position(camera_move * d_t);
    }

    _camera->update(d_t);
}

const mat2 &CameraManager::get_model() {
    return _camera->get_world_model();
}

vec2 CameraManager::to_world(const vec2 &v) {
    if(!_instance) {
        return {-1, -1};
    }
    mat2 inversed_camera_scale = _instance->_camera->get_inversed_scale(),
        camera_translation = _instance->_camera->get_translation();

    vec2 transformed = (v * camera_translation) * inversed_camera_scale;
    return transformed;
}

void CameraManager::resize(const vec2 &v) {
    _camera->update_size(v);
}
