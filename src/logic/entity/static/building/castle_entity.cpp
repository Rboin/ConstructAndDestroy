//
// Created by Sander on 18-4-2017.
//

#include "sdl/image/sdl_image_render_object.h"
#include "castle_entity.h"
#include "entity/resources.h"

CastleEntity::CastleEntity(const mesh *base, vec2 position, float mass) :  BuildingEntity(
        base, position, mass, CASTLE, CASTLETEXTURE) {
    costs = new Resources(0, 0, 5, 0);
}

CastleEntity::CastleEntity(const mesh *base, float mass) : BuildingEntity(
        base, mass, CASTLE, CASTLETEXTURE) {
    costs = new Resources(0, 0, 5, 0);
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