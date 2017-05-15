//
// Created by robin on 5/15/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_H
#define CONSTRUCT_AND_DESTROY_WAVE_H

class Wave {
private:
    static float WAVE_DURATION, STAT_MODIFIER_INCREMENT, SPAWNER_DOWNTIME;
    float _delta_time_wave, _delta_time_spawner, _stat_modifier;

    unsigned int _wave_size, _current_wave;

    /*!
     * Checks whether it's time to move on to the next wave.
     */
    void next_wave();

    /*!
     * Checks whether it's time to spawn a new entity.
     */
    void spawn_entity();

public:
    explicit Wave(unsigned int);

    /*!
     * Increments the timers and calls the next_wave and spawn_entity methods.
     * @param float delta time
     */
    void update(float);

    const unsigned int get_current_wave();

    const float get_stat_modifier();

    const float get_time_wave();
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_H
