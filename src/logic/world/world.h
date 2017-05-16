//
// Created by robin on 2/21/17.
//

#ifndef C_AND_D_PROJECT_WORLD_H
#define C_AND_D_PROJECT_WORLD_H

#include <vector>
#include <string>
#include "types.h"
#include "graph/graph.h"
#include "entity/base_entity.h"
#include "sdl/sdl_render_object.h"

class BSPTree;

class MovingEntity;
class Player;
class BaseEntity;

class World {
private:
    std::vector<BaseEntity *> entities;
    MovingEntity *controllable_character;
    static World *instance;
    Graph *graph;
    std::string texture_path;
    World();
    static World *_instance;

public:
    SDL_RenderObject *_representation;

public:
    ~World();

    void set_render_object(SDL_RenderObject *);

    static World *get_instance();

    /**
     * The render method.
     */
    void render(SDLRenderer *);

    /**
     * The update loop, where we update our entities.
     */
    void update(float);

    World &add_entity(BaseEntity *);

    World &remove_entity(BaseEntity *);

    std::vector<BaseEntity *> get_entities();

    void add_graph(Graph *);

    void add_controllable_character(MovingEntity *);

    Player* getPlayer();
};

#endif //C_AND_D_PROJECT_WORLD_H