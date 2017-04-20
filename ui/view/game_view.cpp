//
// Created by robin on 4/19/17.
//

#include <QDebug>
#include <QGraphicsScene>
#include "game_view.h"
#include "vector.h"
#include "world.h"
#include "timer/game_timer.h"

GameView::GameView(vec2 size, vec2 position) {
    this->setGeometry((int) position.x, (int) position.y, (int) size.x, (int) size.y);

    // Create the scene that we draw on
    _scene = new QGraphicsScene(this);
    _scene->setSceneRect(position.x, position.y, size.x, size.y);
    this->setScene(_scene);
    // Start a timer object
    _timer = new GameTimer();
    // Subscribe the update and render functions to a slot that gets called on timeout()
    GameTimer::connect(_timer, &GameTimer::timeout, this, &GameView::update_view);
    GameTimer::connect(_timer, &GameTimer::timeout, this, &GameView::render_view);
    // Start timer with a timeout of 0ms (or as close to zero)
    _timer->start_timer();
}

void GameView::update_view() {
    // Use the GameTimer::get_delta() method to get the delta time in millis (as a double)
//    _current_world->update((float) _timer->get_delta());
}

void GameView::render_view() {
}

void GameView::paintEvent(QPaintEvent *event) {
    qDebug() << "GameView::paintEvent";
    QLineF line(_scene->sceneRect().topLeft(), _scene->sceneRect().bottomRight());
    QPen pen(Qt::black, 12);
    _scene->addLine(line, pen);
}
