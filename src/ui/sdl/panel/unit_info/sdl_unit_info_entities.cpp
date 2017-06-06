//
// Created by Jeroen on 6/6/2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "sdl_unit_info_entities.h"
#include "../../../../logic/entity/moving/moving_entity.h"

SDLUnitInfoEntities::SDLUnitInfoEntities(std::vector<MovingEntity *> entities, SDL_RenderObject *r) : SDLPanel(r) {
    vec2 size = {40, 40};
    vec2 starting_position = this->get_position()->clone();
    int row = 0;
    int col = 0;

    for(unsigned int i = 0; i < entities.size(); i++) {
        // nicely wrap all images so it fits inside the panel
        if (i * size.x >= this->get_size()->x) {
            row ++;
            col = 0;
        }

        std::string texture = entities.at(i)->get_texture();
        vec2 pos = starting_position + vec2{col * size.x, row * size.y};
        sdl_image_data* image_data = new sdl_image_data{texture};
        SDL_ImageRenderObject* renderer = new SDL_ImageRenderObject(pos, size, image_data);
        SDLPanel* panel = new SDLPanel(renderer);
        add_component(panel);

        col++;
    }
}

void SDLUnitInfoEntities::render(SDLRenderer *renderer, mat2 &m, float d) {
    SDL_UIComponent::render(renderer, m, d);
}
