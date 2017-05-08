//
// Created by Sander on 18-4-2017.
//

#include <sdl/image/sdl_image_render_object.h>
#include "castle_entity.h"

CastleEntity::CastleEntity(const mesh *base, vec2 position, float mass) : BuildingEntity(
        base, position, mass, CASTLE, WAREHOUSETEXTURE) {
}

CastleEntity::CastleEntity(const mesh *base, float mass) : BuildingEntity(
        base, mass, CASTLE, WAREHOUSETEXTURE) {
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