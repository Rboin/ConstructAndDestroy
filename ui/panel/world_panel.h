//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WORLD_PANEL_H
#define CONSTRUCT_AND_DESTROY_WORLD_PANEL_H

#include "component.h"

class GameView;

class WorldPanel : public Component {
private:
    GameView *_game_view;
public:
    WorldPanel(vec2 &, vec2 &);

};


#endif //CONSTRUCT_AND_DESTROY_WORLD_PANEL_H
