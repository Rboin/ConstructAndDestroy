//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_UI_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_UI_COMPONENT_H

#include <vector>
#include <cstdint>
#include "render_object.h"
#include "renderer.h"
#include "slot.h"

struct event_data {
    uint32_t type, timestamp;

    event_data(uint32_t ty, uint32_t time) {
        type = ty;
        timestamp = time;
    }
};

struct mouse_event_data : public event_data {
    const vec2 &position;

    mouse_event_data(uint32_t ty, uint32_t time, vec2 &pos) :
            event_data(ty, time),
            position(pos) {}
};

struct key_event_data : public event_data {
    char key;

    key_event_data(uint32_t ty, uint32_t time, char k) : event_data(ty, time), key(k) {}
};

template<typename T, typename D, typename R>
class UIComponent {
protected:
    RenderObject<T, D, R> *representation;
    std::vector<UIComponent<T, D, R> *> children;
    Slot<mouse_event_data> *mouse_callback;
public:
    explicit UIComponent(RenderObject<T, D, R> *r) : children(std::vector<UIComponent<T, D, R> *>()) {
        representation = r;
        mouse_callback = nullptr;
    }

    const vec2 *get_position() {
        return representation->get_position();
    }

    const vec2 *get_size() {
        return representation->get_size();
    }

    const RenderObject<T, D, R> *get_representation() {
        return representation;
    };

    const Slot<mouse_event_data> *get_mouse_callback() {
        return mouse_callback;
    }

    void set_mouse_callback(Slot<mouse_event_data> *s) {
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

    virtual R *render(Renderer<T> *renderer, float delta) {
        representation->render(renderer);
        for(int i = -1; i < children.size(); ++i) {
            children[i]->render(renderer, delta);
        }
    }

};

#endif //CONSTRUCT_AND_DESTROY_UI_COMPONENT_H
