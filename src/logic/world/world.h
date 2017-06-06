//
// Created by robin on 2/21/17.
//

#ifndef C_AND_D_PROJECT_WORLD_H
#define C_AND_D_PROJECT_WORLD_H

#include <vector>
#include <string>
#include "types.h"

class BaseEntity;
class MovingEntity;
class Player;
class SDL_RenderObject;
class SDLRenderer;

class World {
private:
    static World *_instance;
    std::vector<BaseEntity *> _entities;
    SDL_RenderObject *_representation;
    World();
public:
    ~World();

    void set_render_object(SDL_RenderObject *);

    static World *get_instance();

    /**
     * The render method.
     */
    void render(SDLRenderer *, const mat2 &);

    /**
     * The update loop, where we update our entities.
     */
    void update(float);

    World &add_entity(BaseEntity *);

    World &remove_entity(BaseEntity *);

    std::vector<BaseEntity *> get_entities();

    void remove_dead_entities();

    BaseEntity *get_closest_to(vec2);

    const vec2 &get_size() const;
};

#endif //C_AND_D_PROJECT_WORLD_H