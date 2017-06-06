//
// Created by Jeroen on 5/11/2017.
//

#include <SDL_ttf.h>
#include "sdl/badge/sdl_shortcut_badge_render_object.h"
#include "sdl/label/sdl_cost_label.h"
#include "sdl/label/sdl_name_label.h"
#include "sdl_building_panel.h"
#include "settings.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl_unit_panel.h"
#include "sdl_control_sub_panel.h"
#include "../../../logic/entity/resources.h"
#include "sdl_badge_panel.h"

SDLBuildingPanel::SDLBuildingPanel(SDL_RenderObject *r) : SDLPanel(r) {
    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();

    // for each building that can be created
    // render one panel per building
    for (int i = 0; i < buildings_with_textures.size(); i++) {
        MouseHandlerBuildingPanel *slot = new MouseHandlerBuildingPanel();
        building_with_texture building = buildings_with_textures.at((unsigned int) i);

        vec2 pos = {(float) (100 * i), this->get_representation()->get_position()->clone().y};
        vec2 size = {100, 100};
        vec2 name_label_size = {80, 30};
        vec2 image_pos = {pos.x, pos.y + name_label_size.y};
        vec2 image_size = {50, 50};
        vec2 cost_size = {60, 30};
        vec2 badge_panel_size = {10, 10};


        SDLUnitPanel *unit_panel = new SDLUnitPanel(building.texture, pos, size, image_pos, image_size, building.type,
                                                    building);
        unit_panel->set_mouse_callback(slot);
        mouse_dispatcher->register_callback(unit_panel, slot);

        float posx = pos.x;

        for (int index = ResourceType::GOLD; index < ResourceType::IRON; index++) {
            if (building.cost->get_resources((ResourceType) index) >= 1) {
                TTF_Font *f_font1 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
                sdl_data *sdl_label_data1 = new sdl_data{255, 255, 255, 255};
                vec2 label_pos_cost = {posx, pos.y + size.y - cost_size.y + 10};
                std::string texture = building.cost->get_texture_by_type((ResourceType) index);
                SDLCostLabel *cost_label = new SDLCostLabel(label_pos_cost, cost_size, sdl_label_data1, texture,
                                                            (ResourceType) index, f_font1, building.cost);
                SDLControlSubPanel *cost_panel = new SDLControlSubPanel(cost_label);
                unit_panel->add_component(cost_panel);

                posx += cost_size.x - 10;
            }
        }

        TTF_Font *f_font2 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
        sdl_data *sdl_label_data2 = new sdl_data{255, 255, 255, 255};
        vec2 label_pos_name = {pos.x, pos.y};
        SDLNameLabel *name_label = new SDLNameLabel(label_pos_name, name_label_size, sdl_label_data2, f_font2,
                                                    building.name);
        SDLControlSubPanel *name_panel = new SDLControlSubPanel(name_label);

        // badge displaying shortcut
        TTF_Font *font_shortcut = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 30);
        vec2 badge_panel_position_shortcut = {image_pos.x + 10, image_pos.y + 10};
        sdl_data *badge_color_shortcut = new sdl_data{220, 220, 220, 255};
        SDL_ShortcutBadgeRenderObject *badge_renderer_shortcut = new SDL_ShortcutBadgeRenderObject(
                badge_panel_position_shortcut, badge_panel_size, font_shortcut, std::to_string(i + 1),
                badge_color_shortcut, 10);
        SDLBadgePanel *badge_panel_shortcut = new SDLBadgePanel(badge_renderer_shortcut);


        unit_panel->add_component(name_panel);
        unit_panel->add_component(badge_panel_shortcut);
        this->add_component(unit_panel);
    }
}

SDLBuildingPanel::~SDLBuildingPanel() {
    clear_components();
}

void SDLBuildingPanel::render(SDLRenderer *renderer, mat2 &transformations, float d) {
    SDLPanel::render(renderer, transformations, d);
}

void SDLBuildingPanel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());
    representation->set_position(representation->get_position()->x, v.y - offset.y);
    old_window_size = v;
    resize_children(v);
}
