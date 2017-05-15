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
    static World *_instance;

    std::vector<BaseEntity *> entities;
    Graph *graph;
    SDL_RenderObject *_representation;

    World();

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

    Player* getPlayer();
};

#endif //C_AND_D_PROJECT_WORLD_H