//
// Created by robin on 3/19/17.
//

#include "ui_component.h"
#include <SDL2/SDL.h>

UIComponent::UIComponent(SDL_Rect *s) {
    size = s;
    components = std::map<const char *, UIComponent *>();
    texture = NULL;
}

UIComponent::~UIComponent() {
    SDL_DestroyTexture(this->texture);
}

SDL_Rect *UIComponent::get_size() {
    return size;
}

bool UIComponent::add_component(const char *key, UIComponent *component) {
    if (!components.count(key)) {

        components.insert(std::make_pair(key, component));
        return true;
    }
    return false;
}

bool UIComponent::remove_component(const char *key) {
    if (components.count(key)) {
        components.erase(key);
        return true;
    }
    return false;
}

void UIComponent::update(float d_t) {
    for (std::map<const char *, UIComponent *>::iterator it = components.begin(); it != components.end(); it++) {
        UIComponent *current = (*it).second;
        if (current)
            current->update(d_t);
    }
}

SDL_Texture *UIComponent::draw(SDL_Renderer *renderer) {
    draw_components(renderer);
    return texture;
}

void UIComponent::draw_components(SDL_Renderer *renderer) {
    if (!this->texture) {
        this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                          this->size->w, this->size->h);
    }
    for (std::map<const char *, UIComponent *>::iterator it = components.begin(); it != components.end(); it++) {
        UIComponent *current_component = (*it).second;
        if (!current_component->texture) {
            current_component->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                                           current_component->size->w,
                                                           current_component->size->h);
        }
        SDL_Texture *component_texture = current_component->draw(renderer);
        if (component_texture) {
            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, component_texture, NULL, current_component->size);
        }
    }
}


