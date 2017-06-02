//
// Created by robin on 4/24/17.
//

#include "sdl_panel.h"

SDLPanel::SDLPanel(SDL_RenderObject *r) : SDL_UIComponent(r){
}

SDLPanel::~SDLPanel() {
    this->representation->clear_data();
    for (int i = 0; i < this->children.size(); i++) {
        this->children[i]->clear_components();
        delete this->children[i];
    }
    children.clear();
}
