//
// Created by Jeroen on 5/19/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H

#include <map>
#include "../../../../include/moving_entity_types.h"
#include "sdl_panel.h"

class BuildingEntity;
class SDL_BadgeRenderObject;
class SDL_ProgressbarRenderObject;

/**
 * Renders panels for all entities that can be spawned
 */
class SDLEntityPanel : public SDLPanel {
private:
    std::map<MovingEntityType, SDL_BadgeRenderObject*> _badges;
    BuildingEntity* _building;
    void update_badges();
    void update_badge_color(std::vector<MovingEntityType> orders, MovingEntityType type, SDL_BadgeRenderObject* badge);
public:
    explicit SDLEntityPanel(SDL_RenderObject *, BuildingEntity* selected_building);
    ~SDLEntityPanel();
    void render(SDLRenderer *renderer, float d) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_ENTITY_PANEL_H
