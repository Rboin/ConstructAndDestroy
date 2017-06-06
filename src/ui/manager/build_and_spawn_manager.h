//
// Created by Stephan Schrijver on 29-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_BUILD_AND_SPAWN_MANAGER_H
#define CONSTRUCT_AND_DESTROY_BUILD_AND_SPAWN_MANAGER_H

#include "sdl/panel/sdl_world_panel.h"

class SDLUnitPanel;
class SDLBuildingPanel;

class BuildAndSpawnManager {
private:
    static BuildAndSpawnManager *_instance;

    BuildAndSpawnManager() {}

public:
    ~BuildAndSpawnManager();
    void spawn_spawnable_entity(SDLUnitPanel *);
    void build_building(SDLUnitPanel *);

    static BuildAndSpawnManager *get_instance();


};


#endif //CONSTRUCT_AND_DESTROY_BUILD_AND_SPAWN_MANAGER_H
