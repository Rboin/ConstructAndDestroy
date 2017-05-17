//
// Created by robin on 5/16/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_PROCESS_H
#define CONSTRUCT_AND_DESTROY_WAVE_PROCESS_H

#include "state/state.h"
#include "wave/wave.h"

class WaveEnd : public State<Wave> {
public:
    void enter(Wave *t) override;

    void execute(Wave *t) override;

    void exit(Wave *t) override;
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_PROCESS_H
