//
// Created by Sander on 6-6-2017.
//

#include "entity/upgrade_manager.h"
#include "sdl/image/sdl_image_render_object.h"
#include "research_entity.h"
#include "entity/resources.h"
#include "../../upgrade.h"
#include "settings.h"

ResearchEntity::ResearchEntity(vec2 position, float mass) : BuildingEntity(position, mass, RESEARCH, RESEARCHTEXTURE) {
    costs = new Resources(0, 25, 25, 0);
    upgrades = UpgradeManager::get_instance()->upgrades;
}

ResearchEntity::ResearchEntity(float mass) : BuildingEntity(mass, RESEARCH, RESEARCHTEXTURE) {
    costs = new Resources(0, 25, 25, 0);
    upgrades = UpgradeManager::get_instance()->upgrades;
}

void ResearchEntity::set_transparent_or_border(bool transparent, bool border) {
    sdl_image_data *image;
    if (transparent) {
        if(!border) {
            image = new sdl_image_data{"transp_researchbuilding.png"};
        }
        else
        {
            image = new sdl_image_data("red_transp_researchbuilding.png");
        }
    } else {
        image = new sdl_image_data{"research.png"};
    }

    _representation->set_data(image);
    _representation->clear_data();
}

void ResearchEntity::select() {
    sdl_image_data* entity_data =  new sdl_image_data{"sel_researchbuilding.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}

void ResearchEntity::deselect() {
    sdl_image_data* entity_data =  new sdl_image_data{"research.png"};
    this->_representation->set_data(entity_data);
    this->_representation->clear_data();
}
