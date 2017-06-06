#ifndef CONSTRUCT_AND_DESTROY_SDL_UNIT_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_UNIT_PANEL_H

#include <string>
#include "sdl_panel.h"
#include "settings.h"
#include "building_type.h"

class BuildingEntity;
class SpawnableEntity;
class SDL_ImageRenderObject;

class SDLUnitPanel : public SDLPanel {
private:
    BuildingType _building_type;
    SpawnableEntity* _spawnable_entity;
    BuildingEntity* _building_entity;
    void add_image(std::string texture, vec2 pos, vec2 size);
    building_with_texture _building;
public:
    explicit SDLUnitPanel(std::string texture, vec2 pos, vec2 size, vec2 image_pos, vec2 image_size, SpawnableEntity* spawnable_entity, BuildingEntity* building_entity);
    explicit SDLUnitPanel(std::string texture, vec2 pos, vec2 size, vec2 image_pos, vec2 image_size, BuildingType unit, building_with_texture building);
    ~SDLUnitPanel();

    BuildingType get_building_type();
    SpawnableEntity* get_spawnable_entity();
    BuildingEntity* get_building_entity();
    building_with_texture get_building_information();

    void resize(const vec2 &) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UNIT_PANEL_H
