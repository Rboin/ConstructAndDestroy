#ifndef CONSTRUCT_AND_DESTROY_SDL_UNIT_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_UNIT_PANEL_H


#include "sdl_panel.h"
#include <string>
#include "entity/static/building/building_type.h"

class BuildingEntity;
class SpawnableEntity;
class SDL_ImageRenderObject;

class SDLUnitPanel : public SDLPanel {
private:
    BuildingType _buildingType;
    SpawnableEntity* _spawnableEntity;
    BuildingEntity* _buildingEntity;
    SDL_ImageRenderObject* get_render_object(std::string texture, vec2 pos, vec2 size);
public:
    explicit SDLUnitPanel(std::string texture, vec2 pos, vec2 size, SpawnableEntity* spawnable_entity, BuildingEntity* building_entity);
    explicit SDLUnitPanel(std::string texture, vec2 pos, vec2 size, BuildingType unit);

    BuildingType get_building_type();
    SpawnableEntity* get_spawnable_entity();
    BuildingEntity* get_building_entity();
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UNIT_PANEL_H
