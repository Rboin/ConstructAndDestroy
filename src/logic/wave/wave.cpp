//
// Created by robin on 5/15/17.
//

#include <iostream>
#include "wave.h"

Wave::Wave(unsigned int wave_size) {
    _wave_size = wave_size;
    _current_wave = 1;
    _stat_modifier = 1.0f;
    _delta_time_wave = _delta_time_spawner = 0.0f;

    WAVE_DURATION = 60000.0f;
    STAT_MODIFIER_INCREMENT = .5f;
    SPAWNER_DOWNTIME = WAVE_DURATION / (float) wave_size;
}

void Wave::update(float delta) {
    _delta_time_wave += delta;
    _delta_time_spawner += delta;
    next_wave();
    spawn_entity();
}

void Wave::next_wave() {
    if(_delta_time_wave < WAVE_DURATION) {
        return;
    }
    _delta_time_wave -= WAVE_DURATION;
    _stat_modifier += STAT_MODIFIER_INCREMENT;
    _current_wave++;
}

void Wave::spawn_entity() {
    if(_delta_time_spawner < SPAWNER_DOWNTIME) {
        return;
    }
    _delta_time_spawner -= SPAWNER_DOWNTIME;
    std::cout << "Wave::spawn_entity(): Spawning new entity..." << std::endl;
    // TODO determine what kind of entity to spawn and call SpawningEntity with that type.
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
