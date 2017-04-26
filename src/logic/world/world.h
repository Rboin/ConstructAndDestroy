//
// Created by robin on 2/21/17.
//

#ifndef C_AND_D_PROJECT_WORLD_H
#define C_AND_D_PROJECT_WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include "types.h"
#include "graph/graph.h"
#include "entity/base_entity.h"
#include "sdl/sdl_render_object.h"

class BSPTree;
class MovingEntity;

class World {
private:
    std::vector<BaseEntity *> entities;
    MovingEntity *controllable_character;
    Graph *graph;
    SDL_RenderObject *_representation;

public:

    ~World();

    void set_render_object(SDL_RenderObject *);

    /**
     * The render loop.
     */
    SDL_Texture *render(Renderer<SDL_Renderer> *);

    /**
     * The update loop, where we update our entities.
     */
    void update(float);

    World &add_entity(BaseEntity *);

    void add_graph(Graph *);

    void add_controllable_character(MovingEntity*);

//    void add_partition_tree(BSPTree*);
    void loop(SDL_Renderer *);
};

#endif //C_AND_D_PROJECT_WORLD_H
