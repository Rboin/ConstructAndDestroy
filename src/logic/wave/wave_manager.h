//
// Created by robin on 5/24/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_MANAGER_H
#define CONSTRUCT_AND_DESTROY_WAVE_MANAGER_H

class Wave;

class WaveManager {
private:
    Wave *_wave;
    static WaveManager *_instance;

    WaveManager();

public:
    static WaveManager *get_instance();

    void set_wave(Wave *);

    void reset();

    void reset_player();

    void reset_computer();
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_MANAGER_H
