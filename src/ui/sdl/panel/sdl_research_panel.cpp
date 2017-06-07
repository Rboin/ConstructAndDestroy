//
// Created by Sander on 6-6-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "entity/upgrade_manager.h"
#include "sdl/event/slot/mouse_handler_researchpanel.h"
#include "sdl_research_panel.h"
#include "sdl/badge/sdl_shortcut_badge_render_object.h"
#include "sdl/label/sdl_render_label.h"
#include "sdl/label/sdl_cost_label.h"
#include "sdl/label/sdl_name_label.h"
#include "sdl_entity_panel.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "sdl_progressbar_panel.h"
#include "entity/moving/spawnable_entity.h"
#include "sdl_control_sub_panel.h"

SDLResearchPanel::SDLResearchPanel(SDL_RenderObject *r, BuildingEntity *selected_building) : SDLPanel(r) {
    Player *p = PlayerManager::get_instance()->get_player(player_id);

    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();
    std::vector<Upgrade *> upgrades = selected_building->get_upgrades();

    // for each upgrade of the selected building
    // render one panel per upgrade
    for (int i = 0; i < upgrades.size(); i++) {
        UpgradeType type = upgrades.at((unsigned int) i)->get_upgrade_type();

        vec2 pos = {(float) (100 * i), this->get_representation()->get_position()->clone().y};
        vec2 size = {100, 100};
        vec2 name_label_size = {80, 30};
        vec2 image_pos = {pos.x, pos.y + name_label_size.y};
        vec2 image_size = {50, 50};
        vec2 cost_size = {60, 30};
        vec2 badge_panel_size = {10, 10};
        vec2 check_size = {25,25};
        SDLUnitPanel *unit_panel = new SDLUnitPanel(UpgradeManager::get_instance()->get_texture_of_upgrade(type), pos, size, image_pos, image_size,
                                                    upgrades.at(i));

        sdl_data *sdl_label_data2 = new sdl_data{255, 255, 255, 255};
        TTF_Font *f_font2 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
        vec2 label_pos_name = {pos.x, pos.y};
        SDLNameLabel *name_label = new SDLNameLabel(label_pos_name, name_label_size, sdl_label_data2, f_font2,
                                                    upgrades.at(i)->get_name());
        SDLControlSubPanel *name_panel = new SDLControlSubPanel (name_label);

        ///if it isn't researched add costs, event handlers etc.
        if (!upgrades.at(i)->is_researched()) {
            MouseHandlerResearchPanel *slot = new MouseHandlerResearchPanel();

            unit_panel->set_mouse_callback(slot);
            mouse_dispatcher->register_callback(unit_panel, slot);

            sdl_data *sdl_label_data1 = new sdl_data{255, 255, 255, 255};
            TTF_Font *f_font1 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
            vec2 label_pos_cost = {pos.x, pos.y + size.y - cost_size.y + 10};
            SDLCostLabel *cost_label = new SDLCostLabel(label_pos_cost, cost_size, sdl_label_data1, "gold.png",
                                                        ResourceType::GOLD, f_font1, upgrades.at(i)->get_cost());
            SDLControlSubPanel  *cost_panel = new SDLControlSubPanel (cost_label);

            // badge displaying shortcut
            TTF_Font *font_shortcut = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 30);
            vec2 badge_panel_position_shortcut = {image_pos.x + 10, image_pos.y + 10};
            sdl_data *badge_color_shortcut = new sdl_data{220, 220, 220, 255};
            SDL_ShortcutBadgeRenderObject *badge_renderer_shortcut = new SDL_ShortcutBadgeRenderObject(
                    badge_panel_position_shortcut, badge_panel_size, font_shortcut, std::to_string(i + 1),
                    badge_color_shortcut, 10);
            SDLControlSubPanel  *badge_panel_shortcut = new SDLControlSubPanel (badge_renderer_shortcut);

            unit_panel->add_component(cost_panel);
            unit_panel->add_component(badge_panel_shortcut);
        } else {
            sdl_image_data *sdl_image_data1 = new sdl_image_data{"check.png"};
            vec2 check_pos = {pos.x, pos.y + size.y - check_size.y};
            SDL_RenderObject *image = new SDL_ImageRenderObject(check_pos, check_size ,sdl_image_data1);
            SDLControlSubPanel  *check_panel = new SDLControlSubPanel (image);
            unit_panel->add_component(check_panel);
        }
        unit_panel->add_component(name_panel);
        this->add_component(unit_panel);
    }
}

void SDLResearchPanel::render(SDLRenderer *renderer, mat2 &transformations, float d) {
    SDLPanel::render(renderer, transformations, d);
}

SDLResearchPanel::~SDLResearchPanel() {
    clear_components();
}

void SDLResearchPanel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());
    representation->set_position(representation->get_position()->x, v.y - offset.y);
    representation->set_size({v.x, representation->get_size()->y});
    old_window_size = v;
    resize_children(v);
}
