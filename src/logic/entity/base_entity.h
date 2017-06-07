//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_BASE_GAME_ENTITY_H
#define C_AND_D_PROJECT_BASE_GAME_ENTITY_H

#include <cstdint>
#include "types.h"
#include "vector.h"
#include <string>
#include <map>
#include "textures/texture_types.h"

class Player;
class SDL_RenderObject;
class SDLRenderer;
class SDLStackedPanel;

class BaseEntity {
protected:
    int _type;
    float _mass;
    vec2 _position;
    SDL_RenderObject *_representation;
    Player * _player;

    uint8_t _marking;

    float _max_health;
    float _health;
    float _attack_damage;
    float _attack_speed;
    float _regeneration_rate;

    std::map<std::string, std::string> _info_attributes;

    void upsert_attribute(std::string, std::string);

    void upsert_attribute(std::string image, float value);

public:

    BaseEntity(int, vec2, float, TextureTypes);
    BaseEntity(int, vec2,float);
    virtual ~BaseEntity();

    void set_representation(SDL_RenderObject *);

    vec2 &get_position();

    virtual void set_position(int x, int y);

    virtual void add_to_position(vec2);

    const bool is(int);

    virtual void render(SDLRenderer *, const mat2 &);

    virtual void update(float){};

    std::map<std::string, std::string> get_info_attributes();

    void set_player(int);

    SDL_RenderObject *get_representation();

    Player *get_player();

    void set_selected_texture(TextureTypes);

    void set_deselected_texture(TextureTypes);

    virtual void select();

    virtual void deselect();

    float get_health();

    float get_health_divided_by_max_health();

    float get_attack_damage();

    float get_attack_speed();

    void attack(float);

    void add_mark(uint8_t);

    bool has_mark(uint8_t);

    virtual void multiply_stats(float);

    void regenerate_hp(float d_t);

    void upgrade_health();

    void upgrade_attack();

};

#endif //C_AND_D_PROJECT_BASE_GAME_ENTITY_H
