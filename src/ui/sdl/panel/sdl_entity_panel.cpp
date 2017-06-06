//
// Created by Jeroen on 5/19/2017.
//

#include "sdl/label/sdl_render_label.h"
#include "sdl/label/sdl_cost_label.h"
#include "sdl/label/sdl_name_label.h"
#include "sdl/badge/sdl_badge_render_object.h"
#include "settings.h"
#include "sdl_entity_panel.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "sdl/event/slot/mouse_handler_entitypanel.h"
#include "sdl_progressbar_panel.h"
#include "entity/moving/spawnable_entity.h"

SDLEntityPanel::SDLEntityPanel(SDL_RenderObject *r, BuildingEntity *selected_building) : SDLPanel(r) {
    _building = selected_building;

    Player *p = PlayerManager::get_instance()->get_player(player_id);

    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();
    std::vector<SpawnableEntity *> entities = selected_building->get_spawnable_entities();

    // for each spawnable entity of the selected building
    // render one panel per entity
    for (int i = 0; i < entities.size(); i++) {
        MouseHandlerEntityPanel *slot = new MouseHandlerEntityPanel();
        MovingEntityType type = entities.at((unsigned int) i)->get_entity_type();

        vec2 pos = {(float) (100 * i), this->get_representation()->get_position()->clone().y};
        vec2 size = {100, 100};
        vec2 name_label_size = {80,30};
        vec2 image_pos = {pos.x, pos.y + name_label_size.y};
        vec2 image_size = {50, 50};
        vec2 cost_size = {60, 30};
        vec2 badge_panel_size = {10, 10};

        SDLUnitPanel *unit_panel = new SDLUnitPanel(get_texture_of_entity(type), pos, size, image_pos, image_size, entities.at(i), p->selected_building);
        unit_panel->set_mouse_callback(slot);
        mouse_dispatcher->register_callback(unit_panel, slot);

        SpawnableEntity* se = unit_panel->get_spawnable_entity();


        sdl_data *sdl_label_data1 = new sdl_data{255, 255, 255, 255};
        TTF_Font *f_font1 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
        vec2 label_pos_cost = {pos.x, pos.y + size.y - cost_size.y + 10};
        SDLCostLabel *cost_label = new SDLCostLabel(label_pos_cost, cost_size, sdl_label_data1, "gold.png",
                                                    ResourceType::GOLD, f_font1, se->get_cost());
        SDLPanel *cost_panel = new SDLPanel(cost_label);


        sdl_data *sdl_label_data2 = new sdl_data{255, 255, 255, 255};
        TTF_Font *f_font2 = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
        vec2 label_pos_name = {pos.x, pos.y};
        SDLNameLabel *name_label = new SDLNameLabel(label_pos_name, name_label_size, sdl_label_data2, f_font2, se->get_name());
        SDLPanel *name_panel = new SDLPanel(name_label);

        // badge displaying how many entities are in the order queue
        TTF_Font *font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 25);
        vec2 badge_panel_position = vec2(label_pos_cost.x + cost_size.x, pos.y + size.y - badge_panel_size.y);
        sdl_data *badge_color = new sdl_data{ 0, 255, 0, 255 };
        SDL_BadgeRenderObject *badge_renderer = new SDL_BadgeRenderObject(badge_panel_position, badge_panel_size, font, badge_color, 10);
        SDLPanel *badge_panel = new SDLPanel(badge_renderer);
        _badges.insert(std::pair<MovingEntityType, SDL_BadgeRenderObject*>(type, badge_renderer));

        unit_panel->add_component(cost_panel);
        unit_panel->add_component(name_panel);
        unit_panel->add_component(badge_panel);

        this->add_component(unit_panel);
    }
}

void SDLEntityPanel::render(SDLRenderer *renderer, mat2 &transformations, float d) {
    update_badges();
    SDLPanel::render(renderer, transformations, d);
}

SDLEntityPanel::~SDLEntityPanel() {
    _badges.clear();
    _building= nullptr;
    clear_components();
}


void SDLEntityPanel::update_badges() {
    std::vector<MovingEntityType> orders = _building->get_orders();
    std::map<MovingEntityType, int> counts;

    // find out the sum of the building queue per entity type
    for(std::vector<MovingEntityType>::iterator order = orders.begin();
        order != orders.end();
        ++order) {

        std::map<MovingEntityType, int>::iterator count = counts.find(*order);
        if(count == counts.end()) {
            counts.insert(std::pair<MovingEntityType, int>(*order, 1));
        } else {
            count->second++;
        }
    }

    // for each badge, update the count using the sum that's calculated above
    // and also update the color of the badge
    for(std::map<MovingEntityType, SDL_BadgeRenderObject*>::iterator badge = _badges.begin();
        badge != _badges.end();
        ++badge) {

        std::map<MovingEntityType, int>::iterator count = counts.find(badge->first);

        if (count != counts.end()) {
            badge->second->update_count(count->second);
        } else {
            badge->second->update_count(0);
        }

        update_badge_color(orders, badge->first, badge->second);
    }
}

void SDLEntityPanel::update_badge_color(std::vector<MovingEntityType> orders, MovingEntityType type, SDL_BadgeRenderObject* badge) {
    // color is grey when
    // - this entitytype is not first in the order queue
    // - there are no orders for this entity type
    sdl_data *color = new sdl_data(189, 189, 189, 255);

    if (orders.size() > 0 && orders.front() == type) {
        int total = _building->get_order_time();
        int current = _building->get_delta_time();
        float progress = (float)current / (float)total;

        // if we want to get red -> orange -> green we need to do this check
        if (progress > 0.5) {
            // green is the primary color with a bit of red
            color = new sdl_data(255 * ((1-progress) / 0.5), 255, 0, 255);
        } else {
            // red is the primary color with a bit of green
            color = new sdl_data(255, 255 * (progress * 2), 0, 255);
        }
    }

    badge->set_data(color);
}

void SDLEntityPanel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());
    representation->set_position(representation->get_position()->x, v.y - offset.y);
    representation->set_size({v.x, representation->get_size()->y});
    old_window_size = v;
    resize_children(v);
}
