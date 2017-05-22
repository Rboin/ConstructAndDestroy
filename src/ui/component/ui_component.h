//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_UI_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_UI_COMPONENT_H

#include <vector>
#include <cstdint>
#include "render_object.h"
#include "event/slot.h"

/**
 * @tparam T = Type of renderer, i.e SDL_Renderer.
 * @tparam D = Type of data for RenderObject to draw.
Type o * @tparam R = The result of the RenderObject::render method.
 * @tparam S = f data for the Slot object.
 */
template<typename T, typename D, typename R, typename S, typename K>
class UIComponent {
protected:
    RenderObject<T, D, R> *representation;
    std::vector<UIComponent<T, D, R, S, K> *> children;
    Slot<S> *mouse_callback;
    Slot<K> *key_callback;
public:
    explicit UIComponent(RenderObject<T, D, R> *r) : children(std::vector<UIComponent<T, D, R, S, K> *>()) {
        representation = r;
        mouse_callback = nullptr;
        key_callback = nullptr;
    }

    virtual ~UIComponent() {}

    const vec2 *get_position() {
        return representation->get_position();
    }

    const vec2 *get_size() {
        return representation->get_size();
    }

    virtual RenderObject<T, D, R> *get_representation() {
        return representation;
    };

    const Slot<S> *get_mouse_callback() {
        return mouse_callback;
    }

    void set_mouse_callback(Slot<S> *s) {
        if (mouse_callback) {
            delete mouse_callback;
        }
        mouse_callback = s;
    }

    void set_key_callback(Slot<K> *s) {
        if (key_callback) {
            delete key_callback;
        }
        key_callback = s;
    }

    virtual void set_representation(RenderObject<T, D, R> *ro) {
        if (representation) {
            delete representation;
        }
        representation = ro;
    }

    void add_component(UIComponent *child) {
        children.push_back(child);
    }

    void clear_components() {
        for (int i = 0; i < this->children.size(); i++) {
            this->children[i]->clear_components();
            delete this->children[i];
        }

        this->children.clear();
    }

    void remove_component(UIComponent* component) {
        for (int i = 0; i < this->children.size(); i++) {
            if (this->children.at(i) == component) {
                delete component;
                this->children.erase(this->children.begin() + i);
            }
        }
    }

    bool contains_point(vec2 v) {
        return representation->contains(v);
    }

    virtual void render(T *, float) = 0;

};

#endif //CONSTRUCT_AND_DESTROY_UI_COMPONENT_H
