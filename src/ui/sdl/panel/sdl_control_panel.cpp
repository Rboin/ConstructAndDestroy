//
// Created by Jeroen on 5/19/2017.
//

#include "sdl/label/sdl_name_label.h"
#include "entity/player_manager.h"
#include "sdl_control_panel.h"
#include "entity/player.h"
#include "settings.h"
#include "sdl_building_panel.h"
#include "sdl_entity_panel.h"

BuildingEntity* last_selected_building = nullptr;
bool firstRender = true;

SDLControlPanel* SDLControlPanel::_instance = nullptr;

SDLControlPanel::SDLControlPanel(SDL_RenderObject *r) : SDLPanel(r) {
}

void SDLControlPanel::render(SDLRenderer *renderer, mat2 &transformations, float d) {
    Player* p = PlayerManager::get_instance()->get_player(player_id);

    // optimizaton. clear & add component only when something significant has happened
    // for example, when a building gets selected/deselected
    if (firstRender || last_selected_building != p->selected_building) {
        clear_components();

        if (p->selected_building != nullptr) {
            this->add_component(new SDLEntityPanel(get_similar_representation(), p->selected_building));
        } else {
            this->add_component(new SDLBuildingPanel(get_similar_representation()));
        }

        last_selected_building = p->selected_building;
        firstRender = false;
    }

    SDLPanel::render(renderer, transformations, d);
}

/**
 * Creates a copy of the representation of this panel
 * because we want child panels to be at the same position using the same size and color
 * @return
 */
SDL_RenderObject* SDLControlPanel::get_similar_representation() {
    sdl_data* data = this->get_representation()->get_data();
    sdl_data* similar_data = new sdl_data {data->red, data->green, data->blue, data->alpha};
    return new SDL_RenderObject(this->get_position()->clone(), this->get_size()->clone(), similar_data);
}

SDLControlPanel *SDLControlPanel::get_instance(SDL_RenderObject *r) {
    if (!_instance)
        _instance = new SDLControlPanel(r);
    return _instance;
}

SDLControlPanel *SDLControlPanel::get_instance() {
    if (!_instance)
       throw;
    return _instance;
}

SDLControlPanel::~SDLControlPanel() {
    clear_components();
}

void SDLControlPanel::resize(const vec2 &v) {
    float size_x = old_window_size.x - representation->get_size()->x;
    representation->set_position(representation->get_position()->x, v.y - representation->get_size()->y);
    representation->set_size({v.x - size_x, representation->get_size()->y});
    old_window_size = v;
    resize_children(v);
}
