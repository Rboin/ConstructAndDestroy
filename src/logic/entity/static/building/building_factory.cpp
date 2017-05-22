//
// Created by Stephan Schrijver on 3-5-2017.
//
#include "building_factory.h"
#include "sdl/image/sdl_image_render_object.h"
#include "building_entity.h"
#include "castle_entity.h"
#include "mesh.h"
#include "settings.h"
#include "warehouse_entity.h"

vec2* BuildingFactory::default_shape = new vec2[4] {vec2(-20,20), vec2(20,-20), vec2(20,20), vec2(-20, 20)};

mesh* BuildingFactory::base = new mesh {4, default_shape};

BuildingEntity *BuildingFactory::create(BuildingType type) {
    BuildingEntity *be;
    SDL_ImageRenderObject *iro;
    sdl_image_data *bd;

    if (type == BuildingType::CASTLE) {
        be = new CastleEntity(base, 50);
        bd = new sdl_image_data{"castle.png"};
    } else if (type == BuildingType::WAREHOUSE) {
        be = new WarehouseEntity(base, 50);
        bd = new sdl_image_data{"warehouse.png"};
    }

    iro = new SDL_ImageRenderObject({0, 0}, {50, 50}, bd);
    be->set_player(player_id);
    be->set_representation(iro);
    return be;
}