#include "entity/static/building/building_entity.h"
#include "sdl_unit_panel.h"
#include <sdl/event/sdl_mouse_event_dispatcher.h>
#include "sdl/image/sdl_image_render_object.h"

SDLUnitPanel::SDLUnitPanel(std::string texture, vec2 pos, vec2 size, vec2 image_pos, vec2 image_size, BuildingType unit, building_with_texture building) : SDLPanel(new SDL_RenderObject(pos, size, new sdl_data{0,0,0,0})) {
    _building_type = unit;
    _building = building;

    add_image(texture, image_pos, image_size);
}

SDLUnitPanel::SDLUnitPanel(std::string texture, vec2 pos, vec2 size, vec2 image_pos, vec2 image_size, SpawnableEntity* spawnable_entity, BuildingEntity* building_entity) : SDLPanel(new SDL_RenderObject(pos, size, new sdl_data{0,0,0,0})) {
    _spawnable_entity = spawnable_entity;
    _building_entity = building_entity;

    add_image(texture, image_pos, image_size);
}

void SDLUnitPanel::add_image(std::string texture, vec2 pos, vec2 size) {
    sdl_image_data *building_data = new sdl_image_data{ texture };
    SDL_ImageRenderObject* renderer = new SDL_ImageRenderObject(pos, size, building_data);
    SDLPanel *image_panel = new SDLPanel(renderer);

    this->add_component(image_panel);
}

BuildingType SDLUnitPanel::get_building_type() {
    return _building_type;
}

BuildingEntity* SDLUnitPanel::get_building_entity() {
    return _building_entity;
}

SpawnableEntity* SDLUnitPanel::get_spawnable_entity() {
    return _spawnable_entity;
}

building_with_texture SDLUnitPanel::get_building_information() {
    return _building;
}

