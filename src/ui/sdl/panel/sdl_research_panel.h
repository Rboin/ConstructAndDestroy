//
// Created by Sander on 6-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RESEARCH_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_RESEARCH_PANEL_H

#include <map>
#include "entity/upgrade_type.h"
#include "moving_entity_types.h"
#include "sdl_panel.h"

class BuildingEntity;
class SDL_BadgeRenderObject;

class SDLResearchPanel : public SDLPanel {
public:
    explicit SDLResearchPanel(SDL_RenderObject *, BuildingEntity* selected_building);
    ~SDLResearchPanel();
    void render(SDLRenderer *renderer, mat2 &, float d) override;

    void resize(const vec2 &) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_RESEARCH_PANEL_H
