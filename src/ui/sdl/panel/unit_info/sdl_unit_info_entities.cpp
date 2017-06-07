//
// Created by Jeroen on 6/6/2017.
//

#include <sdl/panel/sdl_stacked_panel.h>
#include "sdl/image/sdl_image_render_object.h"
#include "sdl_unit_info_entities.h"
#include "../../../../logic/entity/moving/moving_entity.h"

SDLUnitInfoEntities::SDLUnitInfoEntities(std::vector<MovingEntity *> entities, SDL_RenderObject *r) : SDLStackedPanel(r, Orientation::horizontal) {
    vec2 size = {40, 40};

    for(unsigned int i = 0; i < entities.size(); i++) {
        std::string texture = entities.at(i)->get_texture();
        vec2 pos = {0,0};
        sdl_image_data* image_data = new sdl_image_data{texture};
        SDL_ImageRenderObject* renderer = new SDL_ImageRenderObject(pos, size, image_data);
        SDLPanel* panel = new SDLPanel(renderer);
        add_component(panel);
    }
}

void SDLUnitInfoEntities::render(SDLRenderer *renderer, mat2 &m, float d) {
    SDLStackedPanel::render(renderer, m, d);
}

void SDLUnitInfoEntities::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());

    representation->set_position(v.x - offset.x, v.y - offset.y);
    old_window_size = v;
    resize_children(v);
}