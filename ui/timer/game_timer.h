//
// Created by robin on 4/20/17.
//

#ifndef CONSTRUCT_AND_DESTROY_GAME_TIMER_H
#define CONSTRUCT_AND_DESTROY_GAME_TIMER_H

#include <QTimer>

class QElapsedTimer;

/**
 * Custom timer class that accepts callbacks.
 * This class is a wrapper for QElapsedTimer, since that class
 * does not handle callbacks.
 */
class GameTimer : public QTimer {
Q_OBJECT
private:
    double _delta_time;
    QElapsedTimer *_timer;
public:
    const static int NANO_MILLI_SIZE = 1000000;

    explicit GameTimer(QObject *parent = 0);

    void start_timer();

    const double get_delta();

public slots:

    void update();
};


#endif //CONSTRUCT_AND_DESTROY_GAME_TIMER_H
