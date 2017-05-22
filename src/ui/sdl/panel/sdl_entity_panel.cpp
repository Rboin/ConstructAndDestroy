//
// Created by Jeroen on 5/19/2017.
//

#include "sdl_entity_panel.h"
#include "sdl/image/sdl_image_render_object.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "sdl/event/slot/mouse_handler_entitypanel.h"
#include "settings.h"

SDLEntityPanel::SDLEntityPanel(SDL_RenderObject *r, BuildingEntity* selected_building) : SDLPanel(r) {
    Player* p = PlayerManager::get_instance()->get_player(player_id);

    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();
    MouseHandlerEntityPanel *slot = new MouseHandlerEntityPanel();
    std::vector<SpawnableEntity*> entities = selected_building->get_spawnable_entities();

    // for each spawnable entity of the selected building
    // render one panel per entity
    for(int i = 0; i < entities.size(); i++) {
        MovingEntityType type = entities.at(i)->get_entity_type();

        vec2 pos = { 100 * i, this->get_representation()->get_position()->clone().y };
        vec2 size = { 75, 75 };
        SDLUnitPanel* unit_panel = new SDLUnitPanel(get_texture_of_entity(type), pos, size, entities.at(i), p->selected_building);
        unit_panel->set_mouse_callback(slot);
        mouse_dispatcher->register_callback(unit_panel, slot);

        mouse_callbacks.push_back(unit_panel);

        this->add_component(unit_panel);
    }
}

void SDLEntityPanel::render(SDLRenderer *renderer, float d) {
    SDLPanel::render(renderer, d);
}

SDLEntityPanel::~SDLEntityPanel() {
    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();

    for(int i = 0; i < mouse_callbacks.size(); i++) {
        mouse_dispatcher->unregister_callback(mouse_callbacks.at(i));
    }
}