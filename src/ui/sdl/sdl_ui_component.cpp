//
// Created by robin on 4/23/17.
//

#include "sdl_ui_component.h"
#include "settings.h"
#include "matrix.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl/sdl_render_object.h"

SDL_UIComponent::SDL_UIComponent(SDL_RenderObject *r) : UIComponent(r) {
    old_window_size = window_size;
}

void SDL_UIComponent::render(SDLRenderer *renderer, mat2 &transformations, float delta) {
    renderer->set_render_target(renderer->get_ui_buffer());
    if(representation) {
        representation->render(renderer, transformations);
    }

    for (int i = 0; i < this->children.size(); i++) {
        children[i]->render(renderer, transformations, delta);
    }
}

SDL_UIComponent::~SDL_UIComponent() {
    if(representation) {
        delete representation;
    }
    if(key_callback) {
        delete key_callback;
    }
    if(mouse_callback) {
        SDL_MouseEventDispatcher *md = SDL_MouseEventDispatcher::get_instance();
        md->unregister_callback(this);
        delete mouse_callback;
    }
    for (unsigned int i = 0; i < children.size(); i++) {
        delete children[i];
    }
    children.clear();
}

void SDL_UIComponent::resize(const vec2 &v) {
    resize_children(v);
}

void SDL_UIComponent::resize_children(const vec2 &v) {
    for (int i = 0; i < this->children.size(); i++) {
        children[i]->resize(v);
    }
}
