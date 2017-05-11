//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_BASE_GAME_ENTITY_H
#define C_AND_D_PROJECT_BASE_GAME_ENTITY_H

#include "types.h"
#include "vector.h"
#include "textures/texture_types.h"

class Player;
class SDL_RenderObject;
class SDLRenderer;

class BaseEntity {
protected:
    int _type;
    float _mass;
    const mesh *_base_representation;
    vec2 _position;
    mesh *_buffer;
    SDL_RenderObject *representation;
    Player * _player;

public:

    BaseEntity(int,const mesh *, vec2, float, TextureTypes);
    BaseEntity(int, const mesh*, vec2,float);

    void set_representation(SDL_RenderObject *);

    vec2 &get_position();

    virtual void set_position(int x, int y);

    virtual void add_to_position(vec2);

    const bool is(int);

    virtual ~BaseEntity();

    virtual void update_render_mesh(const mat2 &);

    virtual void render(SDLRenderer *);

    virtual void update(float){};

    void set_player(int);

    SDL_RenderObject *get_representation();

    Player *get_player();

    void set_selected_texture(TextureTypes);

    void set_deselected_texture(TextureTypes);

    virtual void select();
    virtual void deselect();

};

#endif //C_AND_D_PROJECT_BASE_GAME_ENTITY_H
