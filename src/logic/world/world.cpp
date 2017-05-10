//
// Created by robin on 2/21/17.
//

#include <ctime>
#include <SDL_events.h>
#include <neighbourhood/neighbourhood_manager.h>
#include "world.h"
#include "tree/bsp_tree.h"
#include "tree/bsp_node.h"
#include <entity/moving/moving_entity.h>
#include <entity/player_manager.h>
#include <iostream>
#include "entity/goal/moving_entity_goal/think_goal.h"
#include <typeinfo>
#include <iostream>
#include <entity/static/resource_manager.h>
#include "../globals.cpp"
#include "entity/player.h"
#include "renderer.h"

//declaration of global variable.
extern const std::string path_to_texture;
World *World::_instance = nullptr;

World::World() {
    player = new Player();
    texture_path = path_to_texture + "world.png";
}

World::~World() {
    // Clear world.
}

World *World::instance = nullptr;

World *World::get_instance() {
    if (!instance)
        instance = new World();
    return instance;
}

void World::update(float d_t) {
    for (unsigned int i = 0; i < entities.size(); i++) {
        entities.at(i)->update(d_t);
    }
    ResourceManager *rm = ResourceManager::get_instance();
    rm->replenish_resources(d_t);
//    controllable_character->update(d_t);

    std::vector<int> player_ids = PlayerManager::get_instance()->get_player_ids();
    for (int i = 0; i < player_ids.size(); i++) {
        PlayerManager::get_instance()->get_player(player_ids.at(i))->update();
    }
}

void World::render(SDLRenderer *renderer) {
    _representation->clear_data();
    _representation->render(renderer);

    for (unsigned long i = 0; i < entities.size(); i++) {
        entities.at(i)->render(renderer);
    }
}

void World::loop(SDL_Renderer *renderer) {
//    long last = SDL_GetTicks();
//    while (1) {
//        SDL_Event event;
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT)
//                return;
//                //For testing purpose
//            else if (event.type == SDL_MOUSEBUTTONDOWN) {
//                vec2 pos = {(float) event.button.x, (float) event.button.y};
//
//                int goal = graph->get_node_with_position(pos);
//                int start = graph->get_node_with_position(controllable_character->get_position());
//
//                std::vector<vec2 *> path = graph->a_star_path(graph->nodes[start], graph->nodes[goal]);
//                graph->draw_path.clear();
//                graph->draw_path = path;
//                controllable_character->path = path;
//                controllable_character->get_brain()->set_goal_follow_path();
//            }
//        }
//
//        SDL_RenderClear(renderer);
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//
//        long current_time = SDL_GetTicks();
//        float delta = current_time - last;
//        update(delta);
//        render(renderer);
//
//        last = current_time;
//    }
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
            player->units.push_back(moving_entity);
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

Player* World::getPlayer() {
    return this->player;
}

std::vector<BaseEntity *> World::get_entities() {
    return this->entities;
}

void World::add_graph(Graph *g) {
    graph = g;
}

void World::add_controllable_character(MovingEntity *me) {
    controllable_character = me;
    entities.push_back((BaseEntity *) me);
    NeighbourhoodManager::get_instance()->insert(me);
}

void World::set_render_object(SDL_RenderObject *r) {
    _representation = r;
}
