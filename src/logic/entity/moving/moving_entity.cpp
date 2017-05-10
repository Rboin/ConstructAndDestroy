//
// Created by robin on 3/1/17.
//

#include <cmath>
#include <cfloat>
#include <iostream>
#include <sdl/image/sdl_image_render_object.h>
#include "weapon.h"
#include "entity/weapon/axe_weapon.h"
#include "entity/weapon/bow_weapon.h"
#include "moving_entity.h"
#include "matrix.h"
#include "behaviour/behaviour.h"
#include "tree/bsp_tree.h"
#include "neighbourhood/neighbourhood_manager.h"
#include "behaviour/behaviour_strategy.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "entity/entity_types.h"
#include "entity/goal/moving_entity_goal/job_type.h"


MovingEntity::MovingEntity(const mesh *base, vec2 position, float mass,
                           const float max_force, const float max_speed, JobType jt) :
        MAX_FORCE(max_force), MAX_SPEED(max_speed),
        BaseEntity(MOVING, base, position, mass) {

    _velocity = {0, 0, 0};
    _behaviour = NULL;
    _brain = NULL;
    job_type = jt;
    _possessed = false;
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
    delta_time = d_t;
    if (_brain)
        _brain->process();

    vec2 old = _position.clone();
    //calculate the combined force from each steering behavior
    vec2 steering_force;
    if (_behaviour)
        steering_force = _behaviour->calculate_force(*this, NeighbourhoodManager::get_instance()->get_neighbours(this));
    else
        steering_force = {0, 0, 0};

    //todo:: for now setting velocity to 0 if the steering force = 0, otherwise the flee behaviour
    //todo::keeps moving, even if there is nothing in panic range. This only happens after it show moving.
    if (steering_force.x == 0) {
        _velocity.x = 0;
        _velocity.y = 0;
    }
    //Acceleration = force / mass
    vec2 acceleration = steering_force / _mass;

    //Update the velocity
    _velocity += acceleration * d_t;

    //Make sure vehicle doesn't exceed maximum velocity
    _velocity = _velocity.truncate(MAX_SPEED);

    //Update vehicle's position
    _position += _velocity * d_t;
//    representation->set_position(_position.x, _position.y);
    // Update the render mesh
    update_render_mesh();

    wrap_around(_position);

    // Update the neighbourhood if we've moved
    if (_position != old) {
        NeighbourhoodManager::get_instance()->update(this);
    }

    if (_weapons.size() != 0) {
        select_weapon();
    }
}

float MovingEntity::get_max_speed() {
    return MAX_SPEED;
}

vec2 MovingEntity::get_velocity() {
    return _velocity;
}

void MovingEntity::exorcise() {
    _possessed = false;
}

bool MovingEntity::is_possessed() {
    return _possessed;
}

void MovingEntity::take_possession() {
    _possessed = true;
}

void MovingEntity::update_render_mesh() {
    float angle = std::atan2(_velocity.y, _velocity.x);
    update_render_mesh(mat2::translate(_position) * mat2::rotate(angle));
}

void MovingEntity::update_render_mesh(const mat2 &model) {
    BaseEntity::update_render_mesh(model);
}

void MovingEntity::select_weapon() {
    {
        //if a target is present use fuzzy logic to determine the most desirable
        //weapon.
        NeighbourhoodManager *n = NeighbourhoodManager::get_instance();

        std::vector<BaseEntity *> entities = n->get_neighbours(this);

        if (entities.size()) {
            double DistToTarget = DBL_MAX;
            //calculate the distance to the closest target
            for (int i = 0; i < entities.size(); i++) {
                if (entities.at(i)->is(MOVING)) {
                    double dist = entities.at(i)->get_position().distance(this->get_position());
                    if (dist < DistToTarget) {
                        DistToTarget = dist;
                    }
                }
            }
            //for each weapon in the inventory calculate its desirability given the
            //current situation. The most desirable weapon is selected
            double BestSoFar = DBL_MIN;

            for (int i = 0; i < _weapons.size(); i++) {
                //grab the desirability of this weapon (desirability is based upon
                //distance to target and ammo remaining)
                double score = _weapons.at(i)->get_desirability(DistToTarget);

                //if it is the most desirable so far select it
                if (score > BestSoFar) {
                    BestSoFar = score;

                    //Change the texture of the bos
                    sdl_image_data *newdata = new sdl_image_data("axe.png");
                    representation->set_data(newdata);
                }
            }
        } else {
            sdl_image_data *newdata = new sdl_image_data("bow.png");
            representation->set_data(newdata);
        }

    }
}

void MovingEntity::add_weapons() {
    Axe *axe = new Axe();
    _weapons.push_back((Weapon *) axe);
    Bow *bow = new Bow();
    _weapons.push_back((Weapon *) bow);
}

void MovingEntity::select() {
    std::cout << "Selecting an instance of class MovingEntity is impossible, try selecting a child class." << std::endl;
}

void MovingEntity::deselect() {
    std::cout << "Deselecting an instance of class MovingEntity is impossible, try selecting a child class." << std::endl;

}