//
// Created by robin on 5/15/17.
//

#include <iostream>
#include "wave.h"

Wave::Wave(unsigned int wave_count, unsigned int spawn_amount) {
    _wave_count = wave_count;
    _current_wave = 1;
    _stat_modifier = 1.0f;
    _delta_time_wave = _delta_time_spawner = 0.0f;

    _wave_duration = 10000.0f;
    _stat_modifier_increment = .5f;
    _spawner_downtime = _wave_duration / (float) spawn_amount;
}

void Wave::update(float delta) {
    if(_current_wave > _wave_count) {
        std::cout << "Wave::update(): Finished last wave..." << std::endl;
        return;
    }
    else if(_current_wave <= _wave_count) {
        _delta_time_wave += delta;
        _delta_time_spawner += delta;
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
}

void Wave::spawn_entity() {
    if(_delta_time_spawner < _spawner_downtime) {
        return;
    }
    _delta_time_spawner -= _spawner_downtime;
    std::cout << "Wave::spawn_entity(): Spawning new entity in wave " << _current_wave <<
              " with stat modifier " << _stat_modifier << " at time " << _delta_time_wave << std::endl;
    // TODO determine what kind of entity to spawn and call SpawningEntity with that type.
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

const float Wave::get_time_wave() {
    return _delta_time_wave;
}
