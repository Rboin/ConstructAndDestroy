//
// Created by robin on 4/23/17.
//

#include "sdl_ui_component.h"

SDL_UIComponent::SDL_UIComponent(SDL_UI_RenderObject *r) : UIComponent(r) {

}

SDL_Texture *SDL_UIComponent::render(Renderer<SDL_Renderer> *renderer, float delta) {
    SDL_Texture *texture = representation->render(renderer);
    SDL_SetRenderTarget(renderer->get_engine(), texture);
    for (std::vector<UIComponent<SDL_Renderer, sdl_ui_data, SDL_Texture> *>::iterator it = children.begin();
         it != children.end(); ++it) {

    }
}
