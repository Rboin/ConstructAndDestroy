//
// Created by robin on 2/21/17.
//

#include "neighbourhood/neighbourhood_manager.h"
#include "world.h"
#include "wave/wave.h"
#include "tree/bsp_tree.h"
#include "tree/bsp_node.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "entity/static/resource_manager.h"
#include "settings.h"
#include "entity/player.h"
#include "entity/player_manager.h"

//declaration of global variable.
extern const std::string path_to_texture;
World *World::_instance = nullptr;

World::World() {}

World::~World() {
    // Clear world.
}

World *World::get_instance() {
    if (!_instance)
        _instance = new World();
    return _instance;
}

void World::update(float d_t) {
    for (unsigned int i = 0; i < entities.size(); i++) {
        entities.at(i)->update(d_t);
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

    for (unsigned long i = 0; i < entities.size(); i++) {
        entities.at(i)->render(renderer);
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

    entities.push_back(e);
    NeighbourhoodManager::get_instance()->insert(e);
    return *this;
}

World &World::remove_entity(BaseEntity *e) {
    for (std::vector<BaseEntity *>::iterator iter = entities.begin(); iter != entities.end(); ++iter) {
        if (*iter == e) {
            entities.erase(iter);
            break;
        }
    }
    return *this;
}

std::vector<BaseEntity *> World::get_entities() {
    return this->entities;
}

void World::add_graph(Graph *g) {
    graph = g;
}

void World::set_render_object(SDL_RenderObject *r) {
    _representation = r;
}