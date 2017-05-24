//
// Created by Stephan Schrijver on 29-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_BUILD_AND_SPAWN_MANAGER_H
#define CONSTRUCT_AND_DESTROY_BUILD_AND_SPAWN_MANAGER_H

class SDLUnitPanel;

class BuildAndSpawnManager {
private:
    static BuildAndSpawnManager *_instance;

    BuildAndSpawnManager();

public:
    void spawn_spawnable_entity(SDLUnitPanel *);

    static BuildAndSpawnManager *get_instance();
};


#endif //CONSTRUCT_AND_DESTROY_BUILD_AND_SPAWN_MANAGER_H
