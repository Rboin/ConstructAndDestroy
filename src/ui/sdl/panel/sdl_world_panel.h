//
// Created by robin on 4/26/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_WORLD_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_WORLD_PANEL_H

#include "sdl_panel.h"

class World;

class SDLWorldPanel : public SDLPanel {
private:
    World *_current_world;
public:
    explicit SDLWorldPanel(SDL_RenderObject *);

    SDL_Texture *render(Renderer<SDL_Renderer> *renderer, float d) override;

    void set_world(World *);
};


#endif //CONSTRUCT_AND_DESTROY_SDL_WORLD_PANEL_H
