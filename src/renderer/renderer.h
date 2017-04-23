//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_RENDERER_H
#define CONSTRUCT_AND_DESTROY_RENDERER_H

template<typename T>
class Renderer {
private:
    T *_engine;
public:
    explicit Renderer(T *engine) {
        _engine = engine;
    }

    T *get_engine() {
        return _engine;
    }
};

#endif //CONSTRUCT_AND_DESTROY_RENDERER_H
