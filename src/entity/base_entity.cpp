//
// Created by robin on 3/1/17.
//

#include <matrix.h>
#include <SDL_image.h>
#include <textures/texture_manager.h>
#include "base_entity.h"
#include "mesh.h"
#include "string"
#include "player_manager.h"

BaseEntity::BaseEntity(int type, const mesh *base, vec2 position, float mass, TextureTypes tt) {
    _type = type;
    _mass = mass;
    _base_representation = base;
    _position = position;
    vec2 *buf = new vec2[base->size]{{0, 0}};
    _buffer = new mesh{base->size, buf};
    gTexture = TextureManager::get_instance()->GetTexture(tt);
}

BaseEntity::~BaseEntity() {
    delete[] _buffer->vectors;
    _buffer->vectors = NULL;
    delete _buffer;
    _buffer = NULL;
}

void BaseEntity::update_render_mesh(const mat2 &model) {
    for (int i = 0; i < _base_representation->size; i++) {
        _buffer->vectors[ i ] = _base_representation->vectors[ i ] * model;
    }
}

vec2 &BaseEntity::get_position() {
    return _position;
}

const bool BaseEntity::is(int type) {
    return _type == type;
}

/**
 * A static helper function to create points from vectors.
 * @param m
 * @return
 */
static SDL_Point *to_points(mesh m) {
    SDL_Point *points = new SDL_Point[m.size + 1];
    for (int i = 0; i < m.size; i++) {
        points[ i ] = {(int) m.vectors[ i ].x, (int) m.vectors[ i ].y};
    }
    points[ m.size ] = {(int) m.vectors[ 0 ].x, (int) m.vectors[ 0 ].y};
    return points;
}

void BaseEntity::render(SDL_Renderer *renderer) {
/*
    SDL_Point *points = to_points(*_buffer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLines(renderer, points, _buffer->size + 1);
    delete points;
*/
    if(gTexture){
    SDL_Rect t;
        t.x = _position.x - 20;
        t.y = _position.y - 20;
        t.w = 40;
        t.h = 40;
        SDL_RenderCopy(renderer,gTexture,NULL, &t);
    }
}

const mesh *BaseEntity::get_bounds() {
    return _buffer;
}

void BaseEntity::set_texture(TextureTypes textureTypes) {
    SDL_DestroyTexture(gTexture);
    gTexture = TextureManager::get_instance()->GetTexture(textureTypes);
}

Player *BaseEntity::get_player() {
    return _player;
}

void BaseEntity::set_player(int p) {
    PlayerManager *pm = PlayerManager::get_instance();
    _player = pm->get_player(p);
}

