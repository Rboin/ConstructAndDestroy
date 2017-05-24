//
// Created by robin on 5/18/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SETTINGS_H
#define CONSTRUCT_AND_DESTROY_SETTINGS_H

#include <string>
#include <vector>
#include "../logic/entity/moving/moving_entity_types.h"
#include "../logic/entity/static/building/building_type.h"

const std::string path_to_texture =  "res/textures/";
const std::string path_to_selected_texture =  "res/textures/sel_";
const int player_id = 1;
const int computer_id = 0;
const float wave_pre_stage_time = 60000.0f;
const float wave_preparation_time = 30000.0f;
const float wave_duration = 10000.0f;
const int wave_amount = 10;
const int wave_unit_size = 2;

struct building_with_texture {
    std::string texture;
    BuildingType type;
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
