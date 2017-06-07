//
// Created by Jeroen on 6/1/2017.
//

#include "sdl/sdl_render_object.h"
#include "entity/player.h"
#include "entity/player_manager.h"
#include "settings.h"
#include <string>
#include <iostream>
#include "sdl/panel/unit_info/sdl_unit_info_entities.h"
#include "sdl/panel/unit_info/sdl_unit_info_entity.h"
#include "sdl_unit_info_panel.h"
#include "../../../logic/entity/moving/moving_entity.h"

template<typename T>
std::string get_vector_hash(const std::vector<T> *pointer) {
    std::string total = "";

    for(unsigned int i = 0; i < pointer->size(); i++) {
        total += (char*)&pointer->at(i);
    }

    return total;
}

SDLUnitInfoPanel::SDLUnitInfoPanel(SDL_RenderObject *r) : SDLPanel(r) {
    _previous_units_hash = "";
    _previous_building = nullptr;
}

void SDLUnitInfoPanel::render(SDLRenderer *renderer, mat2 &m, float d) {
    Player *player = PlayerManager::get_instance()->get_player(player_id);

    std::string hash = get_vector_hash(&player->selected_units);

    // don't change this panel when the selection hasn't changed
    if (_previous_building != player->selected_building || _previous_units_hash != hash) {
        clear_components();

        if (player->selected_building != nullptr) {
            add_component(new SDLUnitInfoEntity(player->selected_building, get_similar_representation()));
        } else if (player->selected_units.size() == 1) {
            add_component(new SDLUnitInfoEntity(player->selected_units.front(), get_similar_representation()));
        } else if(player->selected_units.size() > 1) {
            add_component(new SDLUnitInfoEntities(player->selected_units, get_similar_representation()));
        }

        _previous_building = player->selected_building;
        _previous_units_hash = hash;
    }

    SDLPanel::render(renderer, m, d);
}

/**
 * Creates a copy of the representation of this panel
 * because we want child panels to be at the same position using the same size and color
 * @return
 */
SDL_RenderObject* SDLUnitInfoPanel::get_similar_representation() {
    sdl_data* data = this->get_representation()->get_data();
    sdl_data* similar_data = new sdl_data {data->red, data->green, data->blue, data->alpha};
    return new SDL_RenderObject(this->get_position()->clone(), this->get_size()->clone(), similar_data);
}