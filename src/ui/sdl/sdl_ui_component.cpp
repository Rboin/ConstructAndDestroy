//
// Created by robin on 4/23/17.
//

#include "sdl_ui_component.h"

SDL_UIComponent::SDL_UIComponent(SDL_RenderObject *r) : UIComponent(r) {
}

void SDL_UIComponent::render(SDLRenderer *renderer, float delta) {
    representation->render(renderer);

    for (int i = 0; i < this->children.size(); i++) {
        children[i]->render(renderer, delta);
    }
}