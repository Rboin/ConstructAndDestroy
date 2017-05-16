//
// Created by Sander on 18-4-2017.
//

#include <sdl/image/sdl_image_render_object.h>
#include "castle_entity.h"
#include <iostream>
#include <entity/moving/moving_entity_manager.h>

CastleEntity::CastleEntity(const mesh *base, vec2 position, float mass) : BuildingEntity(
        base, position, mass, CASTLE, WAREHOUSETEXTURE) {
    order_time = 10000;
    spawn = this->_position;
    spawn.y += 40;

}

CastleEntity::CastleEntity(const mesh *base, float mass) : BuildingEntity(
        base, mass, CASTLE, WAREHOUSETEXTURE) {
    order_time = 10000;
    spawn = this->_position;
    spawn.y += 40;
}

void CastleEntity::set_to_transparent(bool transparent, bool placeable) {
    sdl_image_data *image;
    if (transparent) {
        if(placeable) {
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

void CastleEntity::update(float d) {
    delta_time += d;
    if(!this->orders.empty()){
        if(delta_time >= order_time){


            this->order_unit_from_factory(_player, spawn, orders.front());

            //remove first from orders.
            orders.erase(orders.begin());
            spawn.y += 40;
            //reset order time.
            delta_time -= order_time;
        }
    };
}

void CastleEntity::order_unit_from_factory(Player *player, vec2 position, MovingEntityType moving_entity_type) {
    std::cout << "ordering" << std::endl;
    MovingEntityManager::get_instance()->add_unit(player, position, moving_entity_type);
}

void CastleEntity::order_unit(MovingEntityType moving_entity_type) {
    delta_time = 0;
    this->orders.push_back(moving_entity_type);

}
