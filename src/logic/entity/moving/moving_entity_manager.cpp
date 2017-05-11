
#include <world/world.h>
#include "moving_entity_manager.h"
#include "moving_entity_factory.h"

MovingEntityManager* MovingEntityManager::instance = nullptr;

MovingEntityManager::MovingEntityManager() {}

MovingEntityManager::~MovingEntityManager() {
    delete this->instance;
}

MovingEntityManager *MovingEntityManager::get_instance() {
    if(!instance){
        instance = new MovingEntityManager();
    }

    return instance;

}

void MovingEntityManager::add_unit(Player *player, vec2 position, MovingEntityType moving_entity_type) {
    MovingEntity* me = MovingEntityFactory::create(player, position, moving_entity_type);

    World::get_instance()->add_controllable_character(me);


}



