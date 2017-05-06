//
// Created by robin on 2/21/17.
//

#include <ctime>
#include <SDL_events.h>
#include <neighbourhood/neighbourhood_manager.h>
#include <SDL_video.h>
#include "world.h"
#include "tree/bsp_tree.h"
#include "tree/bsp_node.h"
#include <cmath>
#include <entity/moving/moving_entity.h>
#include <textures/texture_manager.h>
#include "entity/goal/moving_entity_goal/think_goal.h"
#include <typeinfo>
#include <iostream>
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

void World::update(float d_t) {
    for (unsigned int i = 0; i < entities.size(); i++) {
        entities.at(i)->update(d_t);
    }


//    controllable_character->update(d_t);
}

SDL_Texture *World::render(Renderer<SDL_Renderer> *renderer) {
    _representation->clear_data();
    SDL_Texture *texture = _representation->render(renderer);

    for (unsigned long i = 0; i < entities.size(); i++) {
        SDL_Texture *entity_texture = entities.at(i)->render(renderer);
        SDL_Rect entity_rect = {(int) entities[i]->get_position().x,
                                (int) entities[i]->get_position().y,
                                (int) entities[i]->get_representation()->get_size()->x,
                                (int) entities[i]->get_representation()->get_size()->y};

        SDL_SetRenderTarget(renderer->get_engine(), texture);
        SDL_RenderCopy(renderer->get_engine(), entity_texture, NULL, &entity_rect);
        SDL_SetRenderTarget(renderer->get_engine(), NULL);
    }
    return texture;
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

World *World::get_instance() {
    if (_instance == nullptr)
        _instance = new World();
    return _instance;
}

void World::set_render_object(SDL_RenderObject *r) {
    _representation = r;
}
