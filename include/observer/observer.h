//
// Created by robin on 4/3/17.
//

#ifndef C_AND_D_PROJECT_OBSERVER_H
#define C_AND_D_PROJECT_OBSERVER_H

template<typename T>
class Observable;

template<typename T>
class Observer {
protected:
    Observable<T> *subject;
public:
    virtual void set_subject(Observable<T> *) = 0;

    virtual void update_data() = 0;
};

#endif //C_AND_D_PROJECT_OBSERVER_H
