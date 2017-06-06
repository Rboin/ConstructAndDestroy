//
// Created by robin on 5/31/17.
//

#ifndef CONSTRUCT_AND_DESTROY_CAMERA_MANAGER_H
#define CONSTRUCT_AND_DESTROY_CAMERA_MANAGER_H

#include "types.h"

class World;

class SDLRenderer;

class Camera;

/*!
 * This class acts as a proxy for using the Camera.
 */
class CameraManager {
private:
    Camera *_camera;
    static CameraManager *_instance;

    CameraManager(Camera *);

public:
    virtual ~CameraManager();

    // Deleting these methods as to not get an accidental copy of CameraManager
    CameraManager(CameraManager const &) = delete;

    void operator=(CameraManager const &) = delete;

    static CameraManager *get_instance();

    template<typename W, typename T, typename M>
    void render(T *, W *, void (W::*)(T *, const M &));

    void add_to_position(const vec2 &);

    void update(float);

    void zoom(float);

    const mat2 &get_model();

    static vec2 to_world(const vec2 &);

    void resize(const vec2 &);
};

#endif //CONSTRUCT_AND_DESTROY_CAMERA_MANAGER_H
