//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_GAME_VIEW_H
#define CONSTRUCT_AND_DESTROY_GAME_VIEW_H

#include <QGraphicsView>
#include "types.h"

class World;

class GameTimer;

class GameView : public QGraphicsView {
Q_OBJECT
private:
    World *_current_world;
    GameTimer *_timer;
public:
    GameView(vec2, vec2);

public slots:

    void update_view();

    void render_view();
};


#endif //CONSTRUCT_AND_DESTROY_GAME_VIEW_H
