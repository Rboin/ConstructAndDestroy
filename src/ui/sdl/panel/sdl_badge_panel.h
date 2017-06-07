//
// Created by robin on 6/6/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_BADGE_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_BADGE_PANEL_H

#include "sdl_panel.h"

class SDLBadgePanel : public SDLPanel {
public:
    explicit SDLBadgePanel(SDL_RenderObject *);

    void resize(const vec2 &v) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_BADGE_PANEL_H
