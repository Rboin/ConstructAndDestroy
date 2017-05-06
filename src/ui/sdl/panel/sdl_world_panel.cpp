//
// Created by robin on 4/26/17.
//

#include "sdl_world_panel.h"
#include "world/world.h"

SDLWorldPanel::SDLWorldPanel(SDL_RenderObject *r) : SDLPanel(r){
    _current_world = nullptr;
}

void SDLWorldPanel::set_world(World *world) {
    _current_world = world;
}

SDL_Texture *SDLWorldPanel::render(Renderer<SDL_Renderer> *renderer, float d) {
//    SDLPanel::render(renderer, d);
    _current_world->update(d);
    SDL_Texture *world_texture = _current_world->render(renderer);
    return world_texture;
}
