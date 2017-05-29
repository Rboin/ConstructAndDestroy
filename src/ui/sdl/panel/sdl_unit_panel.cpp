#include "entity/static/building/building_entity.h"
#include "sdl_unit_panel.h"
#include <sdl/event/sdl_mouse_event_dispatcher.h>
#include "sdl/image/sdl_image_render_object.h"

SDLUnitPanel::SDLUnitPanel(std::string texture, vec2 pos, vec2 size, BuildingType unit) : SDLPanel(get_render_object(texture, pos, size)) {
    _buildingType = unit;
}

SDLUnitPanel::SDLUnitPanel(std::string texture, vec2 pos, vec2 size, SpawnableEntity* spawnable_entity, BuildingEntity* building_entity) : SDLPanel(get_render_object(texture, pos, size)) {
    _spawnable_entity = spawnable_entity;
    _building_entity = building_entity;
}

BuildingType SDLUnitPanel::get_building_type() {
    return _buildingType;
}

BuildingEntity* SDLUnitPanel::get_building_entity() {
    return _building_entity;
}

SpawnableEntity* SDLUnitPanel::get_spawnable_entity() {
    return _spawnable_entity;
}

SDL_ImageRenderObject* SDLUnitPanel::get_render_object(std::string texture, vec2 pos, vec2 size) {
    sdl_image_data *building_data = new sdl_image_data{ texture };
    SDL_ImageRenderObject* building_render_object = new SDL_ImageRenderObject(pos, size, building_data);

    return building_render_object;
}