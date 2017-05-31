//
// Created by robin on 2/21/17.
//

#include "entity/entity_marks.h"
#include "world.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "entity/static/resource_manager.h"
#include "entity/player.h"
#include "entity/player_manager.h"

//declaration of global variable.
World *World::_instance = nullptr;

World::World() {}

World::~World() {
    for(int i = 0; i < _entities.size(); i++){
        delete _entities.at(i);
    }
    delete _representation;
    _instance = nullptr;
}

World *World::get_instance() {
    if (!_instance)
        _instance = new World();
    return _instance;
}

void World::update(float d_t) {
    remove_dead_entities();
    for (unsigned int i = 0; i < _entities.size(); i++) {
        _entities.at(i)->update(d_t);
    }
    ResourceManager *rm = ResourceManager::get_instance();
    rm->replenish_resources(d_t);

    std::vector<int> player_ids = PlayerManager::get_instance()->get_player_ids();
    for (int i = 0; i < player_ids.size(); i++) {
        PlayerManager::get_instance()->get_player(player_ids.at(i))->update();
    }
}

void World::render(SDLRenderer *renderer) {
    _representation->render(renderer);

    for (unsigned long i = 0; i < _entities.size(); i++) {
        _entities.at(i)->render(renderer);
    }
}

World &World::add_entity(BaseEntity *e) {

    // Check if variable e is of type MovingEntity by casting it dynamicly.
    // if cast fails, a nullpointer will be returned and the if-statement will be false.
    if(MovingEntity* moving_entity = dynamic_cast<MovingEntity*>(e))
    {
        //TODO: specify which player/AI player the entity should be added to.
        if(moving_entity == nullptr){
            delete moving_entity;
        } else {
            e->get_player()->units.push_back(moving_entity);
        }
    }

    _entities.push_back(e);
    return *this;
}

World &World::remove_entity(BaseEntity *e) {
    for (std::vector<BaseEntity *>::iterator iter = _entities.begin(); iter != _entities.end(); ++iter) {
        if (*iter == e) {
            _entities.erase(iter);
            break;
        }
    }
    return *this;
}

std::vector<BaseEntity *> World::get_entities() {
    return this->_entities;
}

void World::set_render_object(SDL_RenderObject *r) {
    _representation = r;
}

void World::remove_dead_entities() {
    for(std::vector<BaseEntity *>::iterator it = _entities.begin(); it != _entities.end();) {
        if((*it)->has_mark(EntityMark::DEAD)) {
            //clear selected buildings if the entity that is destroyed is a building.
            (*it)->get_player()->clear_selected_building((*it));
            (*it)->get_player()->remove_entity((*it));
            delete (*it);
            it = _entities.erase(it);
        } else {
            ++it;
        }
    }
}

BaseEntity *World::get_closest_to(vec2 v) {
    if(_entities.size() > 0) {
        for(int i = 0; i < _entities.size(); i++) {
            BaseEntity *closest_to_v = _entities.at(i);
            if (closest_to_v->get_representation()->contains(v))
                return closest_to_v;
        }
    }
    return nullptr;
}


