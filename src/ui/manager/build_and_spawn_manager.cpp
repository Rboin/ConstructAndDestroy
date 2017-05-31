//
// Created by Stephan Schrijver on 29-5-2017.
//

#include "entity/moving/spawnable_entity_manager.h"
#include "build_and_spawn_manager.h"
#include "sdl/progressbar/sdl_progressbar_render_object.h"
#include "sdl/panel/sdl_progressbar_panel.h"
#include "sdl/panel/sdl_unit_panel.h"
#include "entity/static/building/building_entity.h"

BuildAndSpawnManager *BuildAndSpawnManager::_instance = nullptr;

BuildAndSpawnManager *BuildAndSpawnManager::get_instance() {
    if (_instance == nullptr) {
        _instance = new BuildAndSpawnManager();
    }
    return _instance;
}

void BuildAndSpawnManager::spawn_spawnable_entity(SDLUnitPanel *sdl_panel) {
    BuildingEntity *building = sdl_panel->get_building_entity();
    SpawnableEntity *spawnable_entity = sdl_panel->get_spawnable_entity();
    bool enough_resources = SpawnableEntityManager::get_instance()->spawn_entity(building, spawnable_entity);

    // spawn_entity returns a building if entity can be spawned
    if (!enough_resources) return;

    // create a progressbarpanel at the center of the unit panel
    // indicating how long it will take to spawn the selected unit
    const vec2 *parent_size = sdl_panel->get_size();
    const vec2 *parent_pos = sdl_panel->get_position();
    vec2 pb_panel_pos = {parent_pos->x + (parent_size->x / 2 - 15),
                         parent_pos->y + parent_size->y + 5}, pb_panel_size = {30, 10};
    sdl_data pb_panel_data = {0, 0, 0, 0};
    SDL_ProgressbarRenderObject *panel_pb = new SDL_ProgressbarRenderObject(pb_panel_pos, pb_panel_size,
                                                                            {255, 255, 255, 255}, &pb_panel_data);
    SDLProgressBarPanel *pb_panel = new SDLProgressBarPanel(panel_pb, building->get_order_time(), sdl_panel);
    sdl_panel->add_component(pb_panel);
}
