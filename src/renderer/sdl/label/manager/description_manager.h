#ifndef CONSTRUCT_AND_DESTROY_DESCRIPTION_MANAGER_H
#define CONSTRUCT_AND_DESTROY_DESCRIPTION_MANAGER_H


#include "vector.h"


class SDLNameLabel;


class DescriptionManager {
private:
    DescriptionManager();

    static SDLNameLabel *description;

public:
    ~DescriptionManager();
    static SDLNameLabel* get_description();
};

#endif //CONSTRUCT_AND_DESTROY_DESCRIPTION_MANAGER_H
