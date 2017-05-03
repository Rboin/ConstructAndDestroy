//
// Created by robin on 3/1/17.
//

#include <vector>
#include <matrix.h>
#include <SDL_image.h>
#include "textures/texture_manager.h"
#include "base_entity.h"
#include "mesh.h"
#include "string"
#include "player_manager.h"
#include "../globals.cpp"
#include <iostream>

extern const std::string path_to_texture;

BaseEntity::BaseEntity(int type, const mesh *base, vec2 position, float mass) {
    _type = type;
    _mass = mass;
    _base_representation = base;
    _position = position;
    vec2 *buf = new vec2[base->size]{{0, 0}};
    _buffer = new mesh{base->size, buf};
}

void BaseEntity::set_representation(SDL_RenderObject *r) {
    representation = r;
}

BaseEntity::~BaseEntity() {
    if (_buffer)
        delete _buffer;
}

void BaseEntity::update_render_mesh(const mat2 &model) {
    for (int i = 0; i < _base_representation->size; i++) {
        _buffer->vectors[i] = _base_representation->vectors[i] * model;
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
        points[i] = {(int) m.vectors[i].x, (int) m.vectors[i].y};
    }
    points[m.size] = {(int) m.vectors[0].x, (int) m.vectors[0].y};
    return points;
}

SDL_Texture *BaseEntity::render(Renderer<SDL_Renderer> *renderer) {
    return representation->render(renderer);
}

const mesh *BaseEntity::get_bounds() {
    return _buffer;
}

Player *BaseEntity::get_player() {
    return _player;
}

void BaseEntity::set_player(int p) {
    PlayerManager *pm = PlayerManager::get_instance();
    _player = pm->get_player(p);
}

void BaseEntity::select() {std::cout << "Can't select base entity" << std::endl;}
void BaseEntity::deselect() {std::cout << "Can't deselect base entity" << std::endl;}

SDL_RenderObject *BaseEntity::get_representation() {
    return representation;
}
