//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_BASE_GAME_ENTITY_H
#define C_AND_D_PROJECT_BASE_GAME_ENTITY_H

#include <vector>
#include <SDL_render.h>
#include "textures/texture_types.h"
#include "entity/player.h"
#include "vector.h"
#include "types.h"

class BaseEntity {
protected:
    int _type;
    float _mass;
    const mesh *_base_representation;
    vec2 _position;
    mesh *_buffer;
    SDL_Texture* gTexture;
    Player * _player;

public:

    BaseEntity(int,const mesh *, vec2, float, TextureTypes);

    vec2 &get_position();

    const bool is(int);

    const mesh *get_bounds();

    virtual ~BaseEntity();

    virtual void update_render_mesh(const mat2 &);

    virtual void render(SDL_Renderer *);

    virtual void update(float){};

    void set_texture(TextureTypes);

    void set_player(int);

    Player *get_player();
};

#endif //C_AND_D_PROJECT_BASE_GAME_ENTITY_H