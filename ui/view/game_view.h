//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_GAME_VIEW_H
#define CONSTRUCT_AND_DESTROY_GAME_VIEW_H

#include <QObject>
#include <QGraphicsView>
#include "types.h"

class World;

class GameView : public QGraphicsView {
Q_OBJECT
private:
    World *_current_world;
    QTimer *_timer;
public:
    GameView(vec2, vec2);

public slots:

    void update();

    void render();
};


#endif //CONSTRUCT_AND_DESTROY_GAME_VIEW_H
