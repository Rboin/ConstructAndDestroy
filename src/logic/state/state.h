//
// Created by Stephan Schrijver on 19-4-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_STATE_H
#define CONSTRUCT_AND_DESTROY_STATE_H

template<class T> class State {
public:

    virtual void enter(T *) = 0;

    virtual void execute(T *) = 0;

    virtual void exit(T *) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_STATE_H
