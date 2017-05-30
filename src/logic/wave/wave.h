//
// Created by robin on 5/15/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_H
#define CONSTRUCT_AND_DESTROY_WAVE_H

#include <vector>
#include "moving_entity_types.h"

class MovingEntityManager;

struct wave_setting {
    float pre_stage_time, preparation_time,
        wave_duration, stat_modifier, stat_modifier_increment;
    unsigned int wave_count, spawn_limit;
};

class Wave {
private:
    bool _pre_stage, _preparing, _finished;
    float _pre_stage_time, _current_prep_time,
        _spawner_downtime, _delta_time_spawner,
        _delta_time_wave, _elapsed_time,
        _current_stat_modifier;

    unsigned int _current_wave, _wave_spawned_count;

    wave_setting &_settings;

    MovingEntityManager *_entity_manager;

    std::vector<MovingEntityType> _spawn_possibilities;

    /*!
     * Checks whether it's time to move on to the next wave.
     */
    void next_wave();

    /*!
     * Checks whether it's time to spawn a new entity.
     */
    void spawn_entity();

public:
    explicit Wave(wave_setting &);

    ~Wave();

    void set_spawn_possibilities(std::vector<MovingEntityType> &);

    /*!
     * Increments the timers and calls the next_wave and spawn_entity methods.
     * @param float delta time
     */
    void update(float);

    const unsigned int get_wave_size() const;

    const unsigned int get_current_wave() const;

    const float get_stat_modifier() const;

    const float get_elapsed_time() const;

    const float get_preparation_time() const;

    const bool is_preparing() const;

    const bool is_finished() const;

    const bool player_won() const;

    const bool computer_won() const;

    const bool time_limit_reached() const;

    const bool spawn_limit_reached() const;

    void reset();
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_H
