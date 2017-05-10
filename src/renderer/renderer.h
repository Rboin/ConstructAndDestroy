//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_RENDERER_H
#define CONSTRUCT_AND_DESTROY_RENDERER_H

template<typename T>
class Renderer {
protected:
    T *engine;
public:
    explicit Renderer(T *e) {
        engine = e;
    }

    T *get_engine() {
        return engine;
    }

    virtual void clear() = 0;

    virtual void show() = 0;
};

#endif //CONSTRUCT_AND_DESTROY_RENDERER_H
