//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_MAIN_WINDOW_H
#define CONSTRUCT_AND_DESTROY_MAIN_WINDOW_H

#include "component/ui_component.h"
#include "event/event_dispatcher.h"

template<typename T, typename D, typename R>
class Window : public UIComponent<T, D, R> {
protected:
    Renderer<T> *renderer;
    EventDispatcher<mouse_event_data> *mouse_event_dispatcher;
    EventDispatcher<key_event_data> *key_event_dispatcher;
public:
    explicit Window(RenderObject<T, D, R> *r) : Window(r, nullptr){}

    explicit Window(RenderObject<T, D, R>  *r, EventDispatcher<mouse_event_data> *mouse) :
            Window(r, mouse, nullptr) {}

    explicit Window(RenderObject<T, D, R>  *r, EventDispatcher<mouse_event_data> *mouse,
                    EventDispatcher<key_event_data> *key) :
            Window(r, mouse, key, nullptr) {}


    explicit Window(RenderObject<T, D, R>  *r, EventDispatcher<mouse_event_data> *mouse,
                    EventDispatcher<key_event_data> *key,
                        Renderer<T> *render) : UIComponent<T, D, R>(r) {
        mouse_event_dispatcher = mouse;
        key_event_dispatcher = key;
        renderer = render;
    }

    void set_renderer(Renderer<T> *r) {
        if (renderer) {
            delete renderer;
        }
        renderer = r;
    }

    void set_mouse_event_dispatcher(EventDispatcher<mouse_event_data> *mouse) {
        if (mouse_event_dispatcher) {
            delete mouse_event_dispatcher;
        }
        mouse_event_dispatcher = mouse;
    }

    void set_key_event_dispatcher(EventDispatcher<key_event_data> *key) {
        if (key_event_dispatcher) {
            delete key_event_dispatcher;
        }
        key_event_dispatcher = key;
    }

    /**
     * The window event and render loop.
     */
    virtual int show() = 0;
};


#endif //CONSTRUCT_AND_DESTROY_MAIN_WINDOW_H
