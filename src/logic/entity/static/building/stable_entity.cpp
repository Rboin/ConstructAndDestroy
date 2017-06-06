//
// Created by Mark on 1-6-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "stable_entity.h"
#include "entity/resources.h"
#include "entity/moving/spawnable_entity.h"

StableEntity::StableEntity(vec2 position, float mass) : BuildingEntity(position, mass, STABLE, STABLETEXTURE) {
    costs = new Resources(0, 0, 50, 0);

    spawnable_entities = {
            new SpawnableEntity(new Resources(10, 0, 0, 0), MovingEntityType::LIGHT_CAVALIER, "Simple knight that will fight your enemies from a horse."),
            new SpawnableEntity(new Resources(15, 0, 0, 0), MovingEntityType::CAVALIER, "This strong unit will fight your enemies"),
            new SpawnableEntity(new Resources(30, 0, 0, 0), MovingEntityType::HEAVY_CAVALIER, "The strongest cavalier of all, will strike fear into your enemies.")
    };

}

StableEntity::StableEntity(float mass) : BuildingEntity(mass, STABLE, STABLETEXTURE) {
    costs = new Resources(0, 0, 50, 0);

    spawnable_entities = {
            new SpawnableEntity(new Resources(10, 0, 0, 0), MovingEntityType::LIGHT_CAVALIER, "Simple knight that will fight your enemies from a horse."),
            new SpawnableEntity(new Resources(15, 0, 0, 0), MovingEntityType::CAVALIER, "This strong unit will fight your enemies"),
            new SpawnableEntity(new Resources(30, 0, 0, 0), MovingEntityType::HEAVY_CAVALIER, "The strongest cavalier of all, will strike fear into your enemies.")
    };

}

void StableEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_horsestable.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}
void StableEntity::deselect() {
    sdl_image_data* entity_data =  new sdl_image_data{"horsestable.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

void StableEntity::set_transparent_or_border(bool transparent, bool border) {
    sdl_image_data *image;
    if (transparent) {
        if(!border) {
            image = new sdl_image_data{"transp_horsestable.png"}; //TODO: Make transparent horse stable and place it here
        }
        else
        {
            image = new sdl_image_data("red_transp_horsestable.png"); //TODO: Make red transparent horse stable and place it here
        }
    } else {
        image = new sdl_image_data{"horsestable.png"};
    }

    _representation->set_data(image);
    _representation->clear_data();
}
