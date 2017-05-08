//
// Created by Stephan on 18-04-2017.
//

#ifndef C_AND_D_PROJECT_BUILDING_MANAGER_H
#define C_AND_D_PROJECT_BUILDING_MANAGER_H

#include <vector>
#include <string>

class BuildingEntity;
class Player;

class BuildingManager {
private:
    BuildingManager();

    static BuildingManager *instance;

    std::vector<BuildingEntity *> buildings;

public:
    ~BuildingManager();

    static BuildingManager *get_instance();

    void choose_building_position(int, std::string);
    std::vector<BuildingEntity *> get_buildings();

    void add_building(Player*, BuildingEntity*);

    void remove_building(Player*, BuildingEntity*);

};

#endif //C_AND_D_PROJECT_BUILDING_MANAGER_H
