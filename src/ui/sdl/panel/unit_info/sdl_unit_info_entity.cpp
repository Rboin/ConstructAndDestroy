//
// Created by Jeroen on 6/6/2017.
//

#include <SDL_ttf.h>
#include <string>
#include <map>
#include "sdl/label/sdl_render_label.h"
#include "sdl/image/sdl_image_render_object.h"
#include "settings.h"
#include "entity/static/building/building_entity.h"
#include "sdl_unit_info_entity.h"
#include "../sdl_stacked_panel.h"
#include "../../../../logic/entity/moving/moving_entity.h"

SDLUnitInfoEntity::SDLUnitInfoEntity(MovingEntity *entity, SDL_RenderObject *r) : SDLUnitInfoEntity(entity, r, entity->get_texture()) {
}

SDLUnitInfoEntity::SDLUnitInfoEntity(BuildingEntity *entity, SDL_RenderObject *r) : SDLUnitInfoEntity(entity, r, get_texture_of_building(entity->get_building_type())) {
}

SDLUnitInfoEntity::SDLUnitInfoEntity(BaseEntity *entity, SDL_RenderObject *r, std::string texture) : SDLStackedPanel(r, Orientation::horizontal) {
    _entity = entity;

    sdl_data* parent_data = this->get_representation()->get_data();

    sdl_image_data *building_data = new sdl_image_data{ texture };
    vec2 image_size = {60, 60};
    SDL_ImageRenderObject* image_renderer = new SDL_ImageRenderObject({}, image_size, building_data);
    SDLPanel* image_panel = new SDLPanel(image_renderer);

    sdl_data* attrstack_data = new sdl_data { parent_data->red, parent_data->green, parent_data->blue, parent_data->alpha };
    _attributes_stackpanel = new SDLStackedPanel(new SDL_RenderObject(this->get_position()->clone(), {60, 100}, attrstack_data), Orientation::vertical);

    add_component(image_panel);
    add_component(_attributes_stackpanel);
}

void SDLUnitInfoEntity::render(SDLRenderer *renderer, mat2 &m, float d) {
    std::map<std::string, const char *> attributes = _entity->get_info_attributes();
    std::map<std::string, const char *>::iterator it;

    for ( it = attributes.begin(); it != attributes.end(); it++ ) {
        if (_labels.count(it->first) == 0) {
            vec2 panel_pos = {};
            sdl_data *sdl_label_data = new sdl_data{255, 255, 255, 255};
            TTF_Font *f_font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
            SDLRenderLabel *label_renderer = new SDLRenderLabel(panel_pos, {50, 30}, sdl_label_data, it->first, it->second, f_font);

            _labels[it->first] = label_renderer;
            _attributes_stackpanel->add_component(new SDLPanel(label_renderer));
        } else {
            SDLRenderLabel *r = _labels[it->first];

            r->set_text(it->second);
        }
    }

    SDLStackedPanel::render(renderer, m, d);
}

void SDLUnitInfoEntity::resize(const vec2 &v) {
    vec2 current_offset = old_window_size - (*representation->get_position());
    old_window_size = v;
    vec2 new_pos = v - current_offset;
    representation->set_position(new_pos.x, new_pos.y);
    resize_children(v);
}

SDLUnitInfoEntity::~SDLUnitInfoEntity() {
    _entity = nullptr;
    _attributes_stackpanel = nullptr;
}