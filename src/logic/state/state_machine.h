//
// Created by Stephan Schrijver on 19-4-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_STATE_MACHINE_H
#define CONSTRUCT_AND_DESTROY_STATE_MACHINE_H

#include "state.h"

template<class T> class State;

template<class T> class StateMachine {
public:
    T *entity;
    State<T> *current_state = nullptr;
    State<T> *previous_state = nullptr;

public:
    StateMachine(T *ent) {
        entity = ent;
    };

    ~StateMachine() {
        if (current_state != nullptr) {
            delete current_state;
            current_state = nullptr;
        }
        if (previous_state != nullptr) {
            delete previous_state;
            previous_state = nullptr;
        }
    }

    void change_state(State<T> *new_state) {
        // Delete state that will never be used again.
        delete previous_state;

        // New state will be set to the current state, so current state will
        // become the previous state
        previous_state = current_state;

        // If there has been a valid previous state, enter exit mode
        // before entering the new state
        if (previous_state != nullptr) {
            previous_state->exit(entity);
        }

        current_state = new_state;
        current_state->enter(entity);
    }

    void clear_state() {
        // New state will be set to the current state, so current state will
        // become the previous state
        previous_state = current_state;

        // If there has been a valid previous state, enter exit mode
        // before entering the new state
        if (previous_state != nullptr) {
            previous_state->exit(entity);
        }

        current_state = nullptr;
    }


    void update() {
        if (current_state != nullptr) {
            current_state->execute(entity);
        }
    }
};

#endif //CONSTRUCT_AND_DESTROY_STATE_MACHINE_H
