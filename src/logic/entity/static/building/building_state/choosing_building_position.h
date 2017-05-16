//
// Created by Stephan Schrijver on 19-4-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_CHOOSING_BUILDING_POSITION_H
#define CONSTRUCT_AND_DESTROY_CHOOSING_BUILDING_POSITION_H

#include "state/state.h"

class Player;

class ChoosingBuildingPosition : public State<Player> {
private:
    int previous_mouse_x;
    int previous_mouse_y;
public:
    void enter(Player*);

    void execute(Player*);

    void exit(Player*);
};

#endif //CONSTRUCT_AND_DESTROY_CHOOSING_BUILDING_POSITION_H
