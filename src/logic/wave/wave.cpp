//
// Created by robin on 5/15/17.
//

#include <iostream>
#include <random>
#include "settings.h"
#include "entity/moving/moving_entity_manager.h"
#include "entity/player_manager.h"
#include "wave.h"
#include "entity/player.h"

Wave::Wave(wave_setting &s) : _settings(s) {
    _finished = false;
    _pre_stage = _preparing = true;
    _pre_stage_time = _settings.pre_stage_time;
    _current_prep_time = _settings.preparation_time;
    _current_wave = 1;
    _current_stat_modifier = _settings.stat_modifier;
    _elapsed_time = _delta_time_wave = _delta_time_spawner = 0.0f;
    _wave_spawned_count = 0;
    _spawner_downtime = (_settings.wave_duration / 2) / (float) _settings.spawn_limit;

    _entity_manager = MovingEntityManager::get_instance();
}

void Wave::update(float delta) {
    if(!_finished) {
        if(_pre_stage) {
            if(_pre_stage_time > 0) {
                _pre_stage_time -= delta;
            } else {
                _pre_stage = false;
                _preparing = false;
            }
            return;
        }


        if(player_won() || computer_won()) {
            _finished = true;
            return;
        }

        if(_preparing && _current_prep_time > 0) {
            _current_prep_time -= delta;
            return;
        } else if(_preparing && _current_prep_time <= 0) {
            _preparing = false;
        }

        if(!_preparing) {
            _delta_time_wave += delta;
            _delta_time_spawner += delta;
            _elapsed_time += delta;
            if(!spawn_limit_reached()) {
                spawn_entity();
            } else if(spawn_limit_reached() && _current_wave < _settings.wave_count) {
                next_wave();
            }
        }
    }
}

void Wave::next_wave() {
    if(_delta_time_wave < _settings.wave_duration) {
        return;
    }
    _wave_spawned_count = 0;
    _delta_time_wave -= _settings.wave_duration;
    _current_stat_modifier += _settings.stat_modifier_increment;
    _current_wave++;
    _current_prep_time = _settings.preparation_time;
    _preparing = true;
}

void Wave::spawn_entity() {
    if(_delta_time_spawner < _spawner_downtime) {
        return;
    }
    _delta_time_spawner -= _spawner_downtime;
    _wave_spawned_count++;
    // Generate a random index from the range of 0 - N
    std::random_device rand_dev;
    // Seed the random generator
    std::mt19937 engine(rand_dev());
    std::uniform_int_distribution<> dist(0, (int) _spawn_possibilities.size() - 1);
    int index = dist(engine);
    _entity_manager->add_unit(PlayerManager::get_instance()->get_player(computer_id), {0,0},
                              _spawn_possibilities[index], _current_stat_modifier);
}

const unsigned int Wave::get_wave_size() const {
    return _settings.wave_count;
}

const unsigned int Wave::get_current_wave() const {
    return _current_wave;
}

const float Wave::get_stat_modifier() const {
    return _current_stat_modifier;
}

const float Wave::get_elapsed_time() const {
    return _elapsed_time;
}

void Wave::set_spawn_possibilities(std::vector<MovingEntityType> &v) {
    _spawn_possibilities = v;
}

const float Wave::get_preparation_time() const {
    if(_pre_stage) {
        return _pre_stage_time;
    } else {
        return _current_prep_time;
    }
}

const bool Wave::is_preparing() const {
    return _preparing || _pre_stage;
}


void Wave::reset() {
    _finished = false;
    _pre_stage = _preparing = true;
    _pre_stage_time = _settings.pre_stage_time;
    _current_prep_time = _settings.preparation_time;
    _current_wave = 1;
    _current_stat_modifier = _settings.stat_modifier;
    _elapsed_time = _delta_time_wave = _delta_time_spawner = 0.0f;
    _wave_spawned_count = 0;
}

const bool Wave::is_finished() const {
    return _finished;
}

const bool Wave::player_won() const {
    bool sufficient_units_player = PlayerManager::get_instance()->get_player(player_id)->units.size() > 0;
    bool sufficient_units_computer = PlayerManager::get_instance()->get_player(computer_id)->units.size() > 0;
    return sufficient_units_player && !sufficient_units_computer && time_limit_reached();
}

const bool Wave::computer_won() const {
    bool sufficient_units_player = PlayerManager::get_instance()->get_player(player_id)->units.size() > 0;
    bool sufficient_units_computer = PlayerManager::get_instance()->get_player(computer_id)->units.size() > 0;
    return sufficient_units_computer && !sufficient_units_player && time_limit_reached();
}

const bool Wave::time_limit_reached() const {
    return _current_wave == _settings.wave_count && _delta_time_wave >= _settings.wave_duration;
}

const bool Wave::spawn_limit_reached() const {
    return _wave_spawned_count == _settings.spawn_limit;
}
