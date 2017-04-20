//
// Created by robin on 4/20/17.
//

#include <QElapsedTimer>
#include <QDebug>
#include "game_timer.h"

GameTimer::GameTimer(QObject *parent) : _delta_time(0),
                                        _timer(new QElapsedTimer()),
                                        QTimer(parent) {
    QObject::connect(this, &GameTimer::timeout, this, &GameTimer::update);
}

void GameTimer::start_timer() {
    start();
    _timer->start();
}

const double GameTimer::get_delta() {
    return _delta_time;
}

void GameTimer::update() {
    // Update the delta time. Normal QElapsedTimer::elapsed() function returns a long
    // which will be 0 most of the time. Convert nanoseconds to millis by hand.
    _delta_time = (double) _timer->nsecsElapsed() / (double) NANO_MILLI_SIZE;
    // Reset the elapsed time since last update call.
    _timer->restart();
}
