//
// Created by robin on 5/16/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_START_H
#define CONSTRUCT_AND_DESTROY_WAVE_START_H

#include "state/state.h"
#include "wave/wave.h"

class WaveStart : public State<Wave> {
public:
    void enter(Wave *t) override;

    void execute(Wave *t) override;

    void exit(Wave *t) override;
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_START_H
