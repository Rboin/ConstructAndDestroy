//
// Created by Sander on 18-4-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "castle_entity.h"
#include "entity/resources.h"


CastleEntity::CastleEntity(const mesh *base, vec2 position, float mass) : BuildingEntity(
        base, position, mass, CASTLE, WAREHOUSETEXTURE) {
    costs = new Resources(0, 5, 0, 0);

    spawnable_entities = {
            new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::LUMBERJACK),
            new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::MINER),
            new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::KNIGHT)
    };
}

CastleEntity::CastleEntity(const mesh *base, float mass) : BuildingEntity(
        base, mass, CASTLE, WAREHOUSETEXTURE) {
    costs = new Resources(0, 5, 0, 0);

    spawnable_entities = {
        new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::LUMBERJACK),
        new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::MINER),
        new SpawnableEntity(new Resources(5, 0, 0, 0), MovingEntityType::KNIGHT)
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

    representation->set_data(image);
    representation->clear_data();
}

void CastleEntity::select(){
    sdl_image_data* entity_data =  new sdl_image_data{"sel_castle.png"};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}

void CastleEntity::deselect(){
    sdl_image_data* entity_data =  new sdl_image_data{"castle.png"};
    this->representation->set_data(entity_data);
    this->representation->clear_data();
}
