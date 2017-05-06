//
// Created by robin on 4/23/17.
//

#include "sdl_ui_component.h"

SDL_UIComponent::SDL_UIComponent(SDL_RenderObject *r) : UIComponent(r) {
}

SDL_Texture *SDL_UIComponent::render(Renderer<SDL_Renderer> *renderer, float delta) {
    SDL_Texture *texture = representation->render(renderer);

    for (int i = 0; i < this->children.size(); i++) {
        SDL_Texture *child_texture = children[i]->render(renderer, delta);
        SDL_Rect child_rectangle = {
                (int) children[i]->get_representation()->get_position()->x,
                (int) children[i]->get_representation()->get_position()->y,
                (int) children[i]->get_representation()->get_size()->x,
                (int) children[i]->get_representation()->get_size()->y
        };
        SDL_SetRenderTarget(renderer->get_engine(), texture);
        SDL_RenderCopy(renderer->get_engine(), child_texture, NULL, &child_rectangle);
        SDL_SetRenderTarget(renderer->get_engine(), NULL);
    }
    return texture;
}