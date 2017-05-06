//
// Created by robin on 4/23/17.
//

#include "sdl_ui_component.h"
#include <cmath>

SDL_UIComponent::SDL_UIComponent(SDL_RenderObject *r) : UIComponent(r) {
    dragging = false;
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

//    if(dragging){
//        //TODO: restructure this function into a render object.
//        this->draw_selection_rect((int)start_drag.x, (int)start_drag.y, (int)end_drag.x, (int)end_drag.y, renderer->get_engine());
//    }
    return texture;
}


//TODO: restructure this function into a render object.
void SDL_UIComponent::draw_selection_rect(int start_x, int start_y, int end_x, int end_y, SDL_Renderer *_renderer) {

    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    SDL_Rect *rect = new SDL_Rect;

    //starting coordinates from the rectangle
    rect->x = start_x;
    rect->y = start_y;

    //coordinates the lines of the rectangle end.
    rect->h = (int) std::abs(start_y - end_y);

    //if rect's origin coordinates are greater then end coordinates use * -1 so the height/weight is negative.
    if (start_y > end_y) { rect->h = rect->h * -1; }

    rect->w = (int) std::abs(end_x - start_x);
    if (start_x > end_x) { rect->w = rect->w * -1; }

    SDL_RenderDrawRect(_renderer, rect);
    SDL_RenderPresent(_renderer);
}