//
// Created by Jeroen on 5/11/2017.
//

#include <SDL_ttf.h>
#include "sdl/label/sdl_cost_label.h"
#include "sdl/label/sdl_name_label.h"
#include "sdl_building_panel.h"
#include "settings.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl_unit_panel.h"

SDLBuildingPanel::SDLBuildingPanel(SDL_RenderObject *r) : SDLPanel(r) {
    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();

    // for each building that can be created
    // render one panel per building
    for (int i = 0; i < buildings_with_textures.size(); i++) {
        MouseHandlerBuildingPanel *slot = new MouseHandlerBuildingPanel();
        building_with_texture building = buildings_with_textures.at((unsigned int) i);

        vec2 pos = {(float) (100 * i), this->get_representation()->get_position()->clone().y};
        vec2 size = {100, 100};
        vec2 name_label_size = {80,30};
        vec2 image_pos = {pos.x, pos.y + name_label_size.y};
        vec2 image_size = {50, 50};
        vec2 cost_size = {60, 30};

        SDLUnitPanel *unit_panel = new SDLUnitPanel(building.texture, pos, size, image_pos, image_size, building.type, building);
        unit_panel->set_mouse_callback(slot);
        mouse_dispatcher->register_callback(unit_panel, slot);


        TTF_Font *f_font1 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
        sdl_data *sdl_label_data1 = new sdl_data{255, 255, 255, 255};
        vec2 label_pos_cost = {pos.x, pos.y + size.y - cost_size.y + 10};
        SDLCostLabel *cost_label = new SDLCostLabel(label_pos_cost, cost_size, sdl_label_data1, "stone.png",
                                                    ResourceType::STONE, f_font1, building.cost);
        SDLPanel *cost_panel = new SDLPanel(cost_label);


        TTF_Font *f_font2 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
        sdl_data *sdl_label_data2 = new sdl_data{255, 255, 255, 255};
        vec2 label_pos_name = {pos.x, pos.y};
        SDLNameLabel *name_label = new SDLNameLabel(label_pos_name, name_label_size, sdl_label_data2, f_font2, building.name);
        SDLPanel *name_panel = new SDLPanel(name_label);


        unit_panel->add_component(cost_panel);
        unit_panel->add_component(name_panel);
        this->add_component(unit_panel);
    }
}

SDLBuildingPanel::~SDLBuildingPanel() {
    clear_components();
}

void SDLBuildingPanel::render(SDLRenderer *renderer, float d) {
    SDLPanel::render(renderer, d);
}
