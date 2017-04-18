//
// Created by robin on 2/21/17.
//

#ifndef C_AND_D_PROJECT_WORLD_H
#define C_AND_D_PROJECT_WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include <graph/graph.h>
#include "types.h"
#include "base_entity.h"

class BSPTree;
class MovingEntity;

class World {
private:
    std::vector<BaseEntity *> entities;
    MovingEntity *controllable_character;
    Graph *graph;
    SDL_Texture* gTexture;

public:
    ~World();
    /**
     * The render loop.
     */
    void render(SDL_Renderer *);

    /**
     * The update loop, where we update our entities.
     */
    void update(float);

    World &add_entity(BaseEntity *);

    void add_graph(Graph *);

    void add_controllable_character(MovingEntity*);

//    void add_partition_tree(BSPTree*);
    void loop(SDL_Renderer *);

    void set_texture(SDL_Renderer *);
};

#endif //C_AND_D_PROJECT_WORLD_H
