#include "sdl_unit_panel.h"
#include "sdl/image/sdl_image_render_object.h"
#include "sdl_control_sub_panel.h"

SDLUnitPanel::SDLUnitPanel(std::string texture, vec2 pos, vec2 size, vec2 image_pos, vec2 image_size,
                           BuildingType unit, building_with_texture building) :
    SDLPanel(new SDL_RenderObject(pos, size, new sdl_data{0,0,0,100})) {

    _building_type = unit;
    _building = building;

    _spawnable_entity = nullptr;
    _building_entity = nullptr;

    add_image(texture, image_pos, image_size);
}

SDLUnitPanel::SDLUnitPanel(std::string texture, vec2 pos, vec2 size, vec2 image_pos, vec2 image_size,
                           SpawnableEntity* spawnable_entity, BuildingEntity* building_entity) :
    SDLPanel(new SDL_RenderObject(pos, size, new sdl_data{0,0,0,100})) {

    _spawnable_entity = spawnable_entity;
    _building_entity = building_entity;

    add_image(texture, image_pos, image_size);
}

void SDLUnitPanel::add_image(std::string texture, vec2 pos, vec2 size) {
    sdl_image_data *building_data = new sdl_image_data{ texture };
    SDL_ImageRenderObject* renderer = new SDL_ImageRenderObject(pos, size, building_data);
    SDLControlSubPanel *image_panel = new SDLControlSubPanel(renderer);
    this->add_component(image_panel);
}

BuildingType SDLUnitPanel::get_building_type() {
    return _building_type;
}

BuildingEntity *SDLUnitPanel::get_building_entity() {
    return _building_entity;
}

SpawnableEntity *SDLUnitPanel::get_spawnable_entity() {
    return _spawnable_entity;
}

building_with_texture SDLUnitPanel::get_building_information() {
    return _building;
}

SDLUnitPanel::~SDLUnitPanel() {
    clear_components();
    _spawnable_entity = nullptr;
    _building_entity = nullptr;
}

void SDLUnitPanel::resize(const vec2 &v) {
    representation->set_position(representation->get_position()->x, v.y - representation->get_size()->y);
    old_window_size = v;
    resize_children(v);
}
