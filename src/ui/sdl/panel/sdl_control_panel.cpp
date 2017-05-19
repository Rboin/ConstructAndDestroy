//
// Created by Jeroen on 5/19/2017.
//

#include <sdl/sdl_render_object.h>
#include <entity/player_manager.h>
#include "sdl_control_panel.h"
#include <entity/player_manager.h>
#include <entity/player.h>
#include "settings.h"
#include "sdl_building_panel.h"
#include "sdl_entity_panel.h"

BuildingEntity* last_selected_building = nullptr;
bool firstRender = true;

SDLControlPanel::SDLControlPanel(SDL_RenderObject *r) : SDLPanel(r) {
}

void SDLControlPanel::render(SDLRenderer *renderer, float d) {
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

    SDLPanel::render(renderer, d);
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