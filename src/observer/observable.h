//
// Created by robin on 4/3/17.
//

#ifndef C_AND_D_PROJECT_SUBJECT_H
#define C_AND_D_PROJECT_SUBJECT_H

#include <vector>
#include "observer.h"

template<typename T>
class Observable {
protected:
    T o_data;
    std::vector<Observer<T> *> observers;
public:
    Observable() {
        observers = std::vector<Observer<T> *>();
    }

    void attach(Observer<T> *o) {
        observers.push_back(o);
    }

    void detach(Observer<T> *o) {
        int f = -1;
        for (unsigned int i = 0; i < observers.size(); ++i) {
            if (observers.at(i) == o) {
                f = i;
                break;
            }
        }
        if (f > -1)
            observers.erase(observers.begin() + f);
    }

    T get_data() {
        return o_data;
    }

    void notify() {
        for (unsigned int i = 0; i < observers.size(); i++) {
            Observer<T> *current = observers[i];
            current->update_data();
        }
    }
};

#endif //C_AND_D_PROJECT_SUBJECT_H
