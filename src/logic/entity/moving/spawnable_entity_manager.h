//
// Created by Stephan Schrijver on 29-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_MANAGER_H
#define CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_MANAGER_H

class BuildingEntity;
class SpawnableEntity;

class SpawnableEntityManager {
private:
    static SpawnableEntityManager* _instance;
    SpawnableEntityManager() {}

public:
    ~SpawnableEntityManager(){}
    static SpawnableEntityManager *get_instance();

    bool spawn_entity(BuildingEntity *, SpawnableEntity *);


};

#endif //CONSTRUCT_AND_DESTROY_SPAWNABLE_ENTITY_MANAGER_H
