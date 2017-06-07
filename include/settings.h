//
// Created by robin on 5/18/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SETTINGS_H
#define CONSTRUCT_AND_DESTROY_SETTINGS_H

#include <string>
#include <vector>
#include "types.h"
#include "vector.h"
#include "building_type.h"
#include "moving_entity_types.h"
#include "building_type.h"

class Resources;

extern float camera_zoom;
extern vec2 window_size;
const vec2 world_size = {3000.0f, 3000.0f};
const unsigned int node_distance = 40;
const vec2 camera_initial_position = {0.0f, 0.0f};
const float camera_initial_scroll_speed = 0.01f;
const float camera_min_zoom = 0.75f;
const float camera_max_zoom = 1.25f;
const float camera_movement_speed = 0.1f;
const float camera_scroll_margin = 20.0f;

const std::string path_to_texture =  "res/textures/";
const std::string path_to_selected_texture =  "res/textures/sel_";
const int player_id = 1;
const int computer_id = 0;
//================ Wave settings ================
const float wave_pre_stage_time = 60000.0f;
const float wave_preparation_time = 30000.0f;
const float wave_duration = 10000.0f;
const float stat_modifier = 1.0f;
const float stat_modifier_increment = 0.25f;
const int wave_amount = 3;
const int wave_unit_size = 1;
//===============================================
struct building_with_texture {
    std::string texture;
    BuildingType type;
    Resources* cost;
    std::string name;
    std::string description;
};

struct entity_with_texture {
    std::string texture;
    MovingEntityType type;
};

extern std::vector<building_with_texture> buildings_with_textures;
extern std::vector<entity_with_texture> entities_with_textures;

extern std::string get_texture_of_entity(MovingEntityType type);
extern std::string get_texture_of_building(BuildingType building);

#endif //CONSTRUCT_AND_DESTROY_SETTINGS_H
