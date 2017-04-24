//
// Created by robin on 3/19/17.
//

#include "world_panel.h"

#include "world/world.h"

WorldPanel::WorldPanel(World *world, SDL_Rect *size) : UIComponent(size) {
    this->_world = world;
}

SDL_Texture *WorldPanel::draw(SDL_Renderer *renderer) {

    SDL_SetRenderTarget(renderer, this->texture);
    this->_world->render(renderer);
    return this->texture;
}

void WorldPanel::update(float d_t) {
    this->_world->update(d_t);
}

