//
// Created by Stephan Schrijver on 2-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_ABORT_PLACING_BUILDING_H
#define CONSTRUCT_AND_DESTROY_ABORT_PLACING_BUILDING_H

#include "entity/state/state.h"

class Player;

template<class T>
class State;

class AbortPlacingBuilding : public State<Player> {
public:
    void enter(Player *);

    void execute(Player *);

    void exit(Player *);
};

#endif //CONSTRUCT_AND_DESTROY_ABORT_PLACING_BUILDING_H
