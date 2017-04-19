//
// Created by robin on 4/19/17.
//

#include <QTimer>
#include <QDebug>
#include <iostream>
#include "game_view.h"
#include "vector.h"

GameView::GameView(vec2 size, vec2 position) {
    this->setGeometry((int) position.x, (int) position.y, (int) size.x, (int) size.y);

    _timer = new QTimer();
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(render()));
    _timer->start();
}

void GameView::update() {
    qDebug() << "UPDATING";
}

void GameView::render() {

    qDebug() << "RENDERING";
}
