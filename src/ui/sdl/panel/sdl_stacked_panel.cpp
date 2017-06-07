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
        float sizex = children.at(i)->get_size()->x;
        float sizey = children.at(i)->get_size()->y;

        if(_orientation == Orientation::horizontal) {
            if (x + sizex > this->get_position()->x + this->get_size()->x) {
                y += sizey;
                x = this->get_position()->x;
            }
        }

        if(_orientation == Orientation::vertical) {
            if (y + sizey > this->get_position()->y + this->get_size()->y) {
                x += sizex;
                y = this->get_position()->y;
            }
        }

        children.at(i)->get_representation()->set_position(x, y);

        if (_orientation == Orientation::horizontal) {
            x += sizex;
//            x += children.at(i)->get_size()->x;

        } else {
//            y += children.at(i)->get_size()->y;

            y += sizey;
        }
    }

    SDLPanel::render(renderer, m, d);
}

void SDLStackedPanel::add_component(SDLPanel *child) {
    SDLPanel::add_component(child);
}


void SDLStackedPanel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());

    representation->set_position(v.x - offset.x, v.y - offset.y);
    old_window_size = v;
    resize_children(v);
}
