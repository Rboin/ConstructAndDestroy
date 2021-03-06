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
    bool dragging;
    vec2 start_drag;
    vec2 end_drag;

    explicit SDLWorldPanel(SDL_RenderObject *);

    virtual ~SDLWorldPanel() override;

    void render(SDLRenderer *renderer, mat2 &, float d) override;
    void draw_selection_rect(int start_x, int start_y, int end_x, int end_y, SDLRenderer* _renderer);
    void set_world(World *);

    void resize(const vec2 &) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_WORLD_PANEL_H
