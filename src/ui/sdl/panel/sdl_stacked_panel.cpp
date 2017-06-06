//
// Created by Jeroen on 6/1/2017.
//

#include "sdl_stacked_panel.h"
#include "sdl_panel.h"

SDLStackedPanel::SDLStackedPanel(SDL_RenderObject *renderer, Orientation orientation) : SDLPanel(renderer) {
    _orientation = orientation;
}

void SDLStackedPanel::render(SDLRenderer *renderer, mat2 &m, float d) {
    std::vector<UIComponent<SDLRenderer, sdl_data, SDL_Texture, sdl_mouse_event_data, sdl_key_event_data>*> children = get_children();

    float x = this->get_position()->x;
    float y = this->get_position()->y;

    for(unsigned i = 0; i < children.size(); i++) {
        children.at(i)->get_representation()->set_position(x, y);

        if (_orientation == Orientation::horizontal) {
            x += children.at(i)->get_size()->x;
        } else {
            y += children.at(i)->get_size()->y;
        }
    }

    SDLPanel::render(renderer, m, d);
}

void SDLStackedPanel::add_component(SDLPanel *child) {
    SDLPanel::add_component(child);
}
