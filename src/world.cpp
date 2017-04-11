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

World::~World() {
    // Clear world.
}

void World::update(float d_t) {
    for (unsigned int i = 0; i < entities.size(); i++) {
        entities.at(i)->update(d_t);
    }
    controllable_character->update(d_t);
}

void World::render(SDL_Renderer *renderer) {
    // Fill panel with white rectangle
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    SDL_RenderFillRect(renderer, NULL);

    SDL_RenderCopy(renderer,gTexture,NULL, NULL);

    for (unsigned long i = 0; i < entities.size(); i++)
        entities.at(i)->render(renderer);
    controllable_character->render(renderer);
    graph->render(renderer);
}

void World::loop(SDL_Renderer *renderer) {
    long last = SDL_GetTicks();
    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return;
                //For testing purpose
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                vec2 pos = {(float) event.button.x, (float) event.button.y};

                int goal = graph->get_node_with_position(pos);
                int start = graph->get_node_with_position(controllable_character->get_position());

                std::vector<vec2 *> path = graph->a_star_path(graph->nodes[start], graph->nodes[goal]);
                graph->draw_path.clear();
                graph->draw_path = path;
                controllable_character->path = path;
                controllable_character->get_brain()->set_goal_follow_path();
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        long current_time = SDL_GetTicks();
        float delta = current_time - last;
        update(delta);
        render(renderer);

        last = current_time;
    }
}

World &World::add_entity(BaseEntity *e) {
    entities.push_back(e);
    NeighbourhoodManager::get_instance()->insert(e);
    return *this;
}

void World::add_graph(Graph *g) {
    graph = g;
}

void World::add_controllable_character(MovingEntity *me) {
    controllable_character = me;
    entities.push_back((BaseEntity *) me);
    NeighbourhoodManager::get_instance()->insert(me);
}

void World::set_texture(SDL_Renderer *) {
    TextureManager *tm = TextureManager::get_instance();
    gTexture = tm->GetTexture(WORLDTEXTURE);
}