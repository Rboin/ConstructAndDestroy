//
// Created by Stephan Schrijver on 3-5-2017.
//
#include "sdl/image/sdl_image_health_render_object.h"
#include "building_factory.h"
#include "building_entity.h"
#include "castle_entity.h"
#include "settings.h"
#include "warehouse_entity.h"
#include "stable_entity.h"
#include "warfactory_entity.h"
#include "research_entity.h"

BuildingEntity *BuildingFactory::create(BuildingType type) {
    BuildingEntity *be;
    SDL_ImageHealthRenderObject *iro;
    sdl_image_data *bd;

    switch(type){
        case BuildingType::CASTLE:
            be = new CastleEntity(50);
            bd = new sdl_image_data{"castle.png"};
            break;
        case BuildingType::WAREHOUSE:
            be = new WarehouseEntity(50);
            bd = new sdl_image_data{"warehouse.png"};
            break;
        case BuildingType::STABLE:
            be = new StableEntity(50);
            bd = new sdl_image_data("horsestable.png");
            break;
        case BuildingType::WARFACTORY:
            be = new WarfactoryEntity(50);
            bd = new sdl_image_data("warfactory.png");
            break;
        case BuildingType ::RESEARCH:
            be = new ResearchEntity(50);
            bd = new sdl_image_data("research.png");
            break;
        default:
            break;
    }

    iro = new SDL_ImageHealthRenderObject({0, 0}, {40, 40}, bd, be);
    be->set_player(player_id);
    be->set_representation(iro);
    return be;
}