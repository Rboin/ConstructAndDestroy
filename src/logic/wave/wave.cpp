//
// Created by robin on 5/15/17.
//

#include <iostream>
#include <random>
#include "settings.h"
#include "entity/moving/moving_entity_manager.h"
#include "entity/player_manager.h"
#include "wave.h"

Wave::Wave(float preparation, unsigned int wave_count, unsigned int spawn_amount) {
    _preparing = true;
    _finished = false;
    _prep_time = _current_prep_time = preparation;
    _wave_count = wave_count;
    _current_wave = 1;
    _stat_modifier = 1.0f;
    _elapsed_time = _delta_time_wave = _delta_time_spawner = 0.0f;

    _wave_duration = 10000.0f;
    _stat_modifier_increment = .5f;
    _spawner_downtime = _wave_duration / (float) spawn_amount;

    _entity_manager = MovingEntityManager::get_instance();
}

void Wave::update(float delta) {
    if(_current_wave >= _wave_count) {
        std::cout << "Wave::update(): Finished last wave..." << std::endl;
        _finished = true;
        return;
    }
    if(_current_prep_time > 0) {
        _current_prep_time -= delta;
        return;
    } else if(_current_prep_time <= 0) {
        _preparing = false;
    }
    if(!_preparing && _current_wave <= _wave_count) {
        _delta_time_wave += delta;
        _delta_time_spawner += delta;
        _elapsed_time += delta;
        spawn_entity();
        next_wave();
    }
}

void Wave::next_wave() {
    if(_delta_time_wave < _wave_duration) {
        return;
    }
    _delta_time_wave -= _wave_duration;
    _stat_modifier += _stat_modifier_increment;
    _current_wave++;
    _current_prep_time = _prep_time;
    _preparing = true;
}

void Wave::spawn_entity() {
    if(_delta_time_spawner < _spawner_downtime) {
        return;
    }
    _delta_time_spawner -= _spawner_downtime;

    // Generate a random index from the range of 0 - N
    std::random_device rand_dev;
    // Seed the random generator
    std::mt19937 engine(rand_dev());
    std::uniform_int_distribution<> dist(0, (int) _spawn_possibilities.size() - 1);
    int index = dist(engine);
    _entity_manager->add_unit(PlayerManager::get_instance()->get_player(computer_id), {0,
                                                                                       0}, _spawn_possibilities[index]);
}

const unsigned int Wave::get_wave_size() {
    return _wave_count;
}

const unsigned int Wave::get_current_wave() {
    return _current_wave;
}

const float Wave::get_stat_modifier() {
    return _stat_modifier;
}

const float Wave::get_elapsed_time() {
    return _elapsed_time;
}

void Wave::set_spawn_possibilities(std::vector<MovingEntityType> &v) {
    _spawn_possibilities = v;
}

const float Wave::get_preparation_time() {
    return _current_prep_time;
}

const bool Wave::is_preparing() {
    return _preparing;
}
