//
// Created by robin on 4/23/17.
//

#include "sdl_ui_component.h"

SDL_UIComponent::SDL_UIComponent(SDL_UI_RenderObject *r) : UIComponent(r) {

}

SDL_Texture *SDL_UIComponent::render(Renderer<SDL_Renderer> *renderer, float delta) {
    SDL_Texture *texture = representation->render(renderer);
    SDL_SetRenderTarget(renderer->get_engine(), NULL);
    SDL_Rect texture_rect = {
            (int) representation->get_position()->x, (int) representation->get_position()->y,
            (int) representation->get_size()->x, (int) representation->get_size()->y
    };
    SDL_RenderCopy(renderer->get_engine(), texture, NULL, &texture_rect);

    for (int i = 0; i < this->children.size(); i++) {
        children[i]->render(renderer, delta);
    }
    return texture;
}
