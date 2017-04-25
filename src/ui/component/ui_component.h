//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_UI_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_UI_COMPONENT_H

#include <vector>
#include <cstdint>
#include "render_object.h"
#include "renderer.h"
#include "event/slot.h"

/**
 * @tparam T = Type of renderer, i.e SDL_Renderer.
 * @tparam D = Type of data for RenderObject to draw.
 * @tparam R = The result of the RenderObject::render method.
 * @tparam S = Type of data for the Slot object.
 */
template<typename T, typename D, typename R, typename S>
class UIComponent {
protected:
    RenderObject<T, D, R> *representation;
    std::vector<UIComponent<T, D, R, S> *> children;
    Slot<S> *mouse_callback;
public:
    explicit UIComponent(RenderObject<T, D, R> *r) : children(std::vector<UIComponent<T, D, R, S> *>()) {
        representation = r;
        mouse_callback = nullptr;
    }

    const vec2 *get_position() {
        return representation->get_position();
    }

    const vec2 *get_size() {
        return representation->get_size();
    }

    RenderObject<T, D, R> *get_representation() {
        return representation;
    };

    const Slot<S> *get_mouse_callback() {
        return mouse_callback;
    }

    void set_mouse_callback(Slot<S> *s) {
        if(mouse_callback) {
            delete mouse_callback;
        }
        mouse_callback = s;
    }

    void set_representation(RenderObject<T, D, R> * ro) {
        if(representation) {
            delete representation;
        }
        representation = ro;
    }

    void add_component(UIComponent *child) {
        children.push_back(child);
    }

    bool contains_point(vec2 v) {
        return representation->contains(v);
    }

    virtual R *render(Renderer<T> *renderer, float delta) {
        representation->render(renderer);
        for(int i = -1; i < children.size(); ++i) {
            children[i]->render(renderer, delta);
        }
        return nullptr;
    }

};

#endif //CONSTRUCT_AND_DESTROY_UI_COMPONENT_H
