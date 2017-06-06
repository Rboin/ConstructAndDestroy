//
// Created by Mark on 6-6-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "warfactory_entity.h"
#include "entity/resources.h"
#include "entity/moving/spawnable_entity.h"

WarfactoryEntity::WarfactoryEntity(vec2 position, float mass) : BuildingEntity(position, mass, WARFACTORY, STABLETEXTURE) {
    costs = new Resources(0, 50, 50, 0);

    spawnable_entities = {
            new SpawnableEntity(new Resources(15, 0, 0, 0), MovingEntityType::MERCENARY, "Wielding a big sword, lots of damage but not very durable."),
            new SpawnableEntity(new Resources(30, 0, 0, 0), MovingEntityType::JUGGERNAUT, "Almost unkillable unit, very strong but very slow.")
    };

}

WarfactoryEntity::WarfactoryEntity(float mass) : BuildingEntity(mass, WARFACTORY, STABLETEXTURE) {
    costs = new Resources(0, 50, 50, 0);

    spawnable_entities = {
            new SpawnableEntity(new Resources(15, 0, 0, 0), MovingEntityType::MERCENARY, "Wielding a big sword, lots of damage but not very durable."),
            new SpawnableEntity(new Resources(30, 0, 0, 0), MovingEntityType::JUGGERNAUT, "Almost unkillable unit, very strong but very slow.")
    };
}

void WarfactoryEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_warfactory.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}
void WarfactoryEntity::deselect() {
    sdl_image_data* entity_data =  new sdl_image_data{"warfactory.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

void WarfactoryEntity::set_transparent_or_border(bool transparent, bool border) {
    sdl_image_data *image;
    if (transparent) {
        if(!border) {
            image = new sdl_image_data{"transp_warfactory.png"}; //TODO: Make transparent horse stable and place it here
        }
        else
        {
            image = new sdl_image_data("red_transp_warfactory.png"); //TODO: Make red transparent horse stable and place it here
        }
    } else {
        image = new sdl_image_data{"warfactory.png"};
    }

    _representation->set_data(image);
    _representation->clear_data();
}

