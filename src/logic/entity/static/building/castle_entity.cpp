//
// Created by Sander on 18-4-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "castle_entity.h"
#include "entity/resources.h"
#include "entity/moving/spawnable_entity.h"



CastleEntity::CastleEntity(vec2 position, float mass) : BuildingEntity(
        position, mass, CASTLE, WAREHOUSETEXTURE) {
    costs = new Resources(0,25,25,0);

    spawnable_entities = {
            new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::LUMBERJACK, "This unit can gather wood"),
            new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::MINER, "This unit will mine resources like stone and gold"),
            new SpawnableEntity(new Resources(10, 0, 0, 0), MovingEntityType::KNIGHT, "This unit will fight your enemies")
    };
}


CastleEntity::CastleEntity(float mass) : BuildingEntity(
        mass, CASTLE, WAREHOUSETEXTURE) {
    costs = new Resources(0,25,25,0);

    spawnable_entities = {
            new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::LUMBERJACK, "This unit can gather wood"),
            new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::MINER, "This unit will mine resources like stone and gold"),
            new SpawnableEntity(new Resources(10, 0, 0, 0), MovingEntityType::KNIGHT, "This unit will fight your enemies")
    };
}


void CastleEntity::set_transparent_or_border(bool transparent, bool border) {
    sdl_image_data *image;
    if (transparent) {
        if(!border) {
            image = new sdl_image_data{"transp_castle.png"};
        }
        else
        {
            image = new sdl_image_data("red_transp_castle.png");
        }
    } else {
        image = new sdl_image_data{"castle.png"};
    }

    _representation->set_data(image);
    _representation->clear_data();
}

void CastleEntity::select(){
    sdl_image_data* entity_data =  new sdl_image_data{"sel_castle.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

void CastleEntity::deselect(){
    sdl_image_data* entity_data =  new sdl_image_data{"castle.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}
