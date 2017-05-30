//
// Created by robin on 4/23/17.
//

#include "sdl_ui_component.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl/sdl_render_object.h"

SDL_UIComponent::SDL_UIComponent(SDL_RenderObject *r) : UIComponent(r) {
}

void SDL_UIComponent::render(SDLRenderer *renderer, float delta) {
    if(representation) {
        representation->render(renderer);
    }

    for (int i = 0; i < this->children.size(); i++) {
        children[i]->render(renderer, delta);
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
