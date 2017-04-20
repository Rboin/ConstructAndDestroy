//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_GAME_VIEW_H
#define CONSTRUCT_AND_DESTROY_GAME_VIEW_H

#include <QGraphicsView>
#include "types.h"

class QGraphicsScene;
class GameTimer;
class World;

class GameView : public QGraphicsView {
Q_OBJECT
private:
    QGraphicsScene *_scene;
    GameTimer *_timer;
    World *_current_world;

public:
    GameView(vec2, vec2);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:

    void update_view();

    void render_view();
};


#endif //CONSTRUCT_AND_DESTROY_GAME_VIEW_H
