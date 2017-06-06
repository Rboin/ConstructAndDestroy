//
// Created by robin on 3/1/17.
//

#include <cmath>
#include <iostream>
#include "sdl/image/sdl_image_render_object.h"
#include "moving_entity.h"
#include "behaviour/behaviour.h"
#include "behaviour/behaviour_strategy.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "entity/entity_types.h"

MovingEntity::MovingEntity(vec2 position, float mass, JobType jt) : BaseEntity(MOVING, position, mass) {
    _velocity = {0, 0, 0};
    _behaviour = NULL;
    _brain = NULL;
    _job_type = jt;
    _engaged = false;
}

MovingEntity::~MovingEntity() {
    _behaviour = nullptr;
    _brain = nullptr;
    while (!_path.empty()) {
        _path.pop();
    }
}

Behaviour *MovingEntity::get_behaviour() {
    return _behaviour;
}

void MovingEntity::set_behaviour(Behaviour *b) {
    _behaviour = b;
}

ThinkGoal *MovingEntity::get_brain() {
    return _brain;
}

void MovingEntity::set_goal(ThinkGoal *g) {
    _brain = g;
}

void MovingEntity::update(float d_t) {
    _delta_time = d_t;
    if (_brain)
        _brain->process();

    vec2 old = _position.clone();
    //calculate the combined force from each steering behavior
    vec2 steering_force;
    if (_behaviour)
        steering_force = _behaviour->calculate_force(*this);
    else
        steering_force = {0, 0, 0};

    if (steering_force.x == 0 && steering_force.y == 0) {
        _velocity.x = 0;
        _velocity.y = 0;
    }
    //Acceleration = force / mass
    vec2 acceleration = steering_force / _mass;

    //Update the velocity
    _velocity += acceleration * d_t;

    //Make sure vehicle doesn't exceed maximum velocity
    _velocity = _velocity.truncate(max_speed);

    //Update vehicle's position
    add_to_position(_velocity * d_t);
}

float MovingEntity::get_max_speed() {
    return max_speed;
}

vec2 MovingEntity::get_velocity() {
    return _velocity;
}

void MovingEntity::select() {
    std::cout << "Selecting an instance of class MovingEntity is impossible, try selecting a child class." << std::endl;
}

void MovingEntity::deselect() {
    std::cout << "Deselecting an instance of class MovingEntity is impossible, try selecting a child class."
              << std::endl;
}

std::string MovingEntity::get_texture() {
    std::cout << "you cannot get the texture of a moving entity class itself." << std::endl;
}

void MovingEntity::set_texture(std::string src) {
    std::cout << "you cannot set the texture of a moving entity class itself." << std::endl;
}

bool MovingEntity::is_engaged() {
    return _engaged;
}

void MovingEntity::set_engaged(bool engaged) {
    _engaged = engaged;
}

void MovingEntity::set_job_type(JobType jt) {
    _job_type = jt;
}

void MovingEntity::set_carrying(float c) {
    carrying = c;
}

float MovingEntity::get_carrying() {
    return carrying;
}

JobType MovingEntity::get_job_type() {
    return _job_type;
}

void MovingEntity::set_path(std::stack<vec2 *> p) {
    _path = p;
}

std::stack<vec2 *> &MovingEntity::get_path() {
    return _path;
}

float MovingEntity::get_delta_time() {
    return _delta_time;
}
