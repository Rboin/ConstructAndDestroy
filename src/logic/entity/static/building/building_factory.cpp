//
// Created by Stephan Schrijver on 3-5-2017.
//
#include "building_factory.h"
#include <sdl/image/sdl_image_render_object.h>
#include "building_entity.h"
#include "castle_entity.h"
#include "mesh.h"

vec2* BuildingFactory::default_shape = new vec2[4] {vec2(-20,20), vec2(20,-20), vec2(20,20), vec2(-20, 20)};

mesh* BuildingFactory::base = new mesh {4, default_shape};

BuildingEntity *BuildingFactory::create(std::string type) {
    BuildingEntity *be;
    SDL_ImageRenderObject *iro;
    sdl_image_data *bd;

    if (type == "castle") {
        be = new CastleEntity(base, 50);
        bd = new sdl_image_data{"castle.png"};
    }

    iro = new SDL_ImageRenderObject({0, 0}, {40, 40}, bd);
    be->set_representation(iro);
    return be;
}